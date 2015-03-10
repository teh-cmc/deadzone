package otolib

import (
	"encoding/json"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"path/filepath"
	"sync"

	"github.com/teh-cmc/otogonf/otolib/Godeps/_workspace/src/github.com/ant0ine/go-json-rest/rest"
	"github.com/teh-cmc/otogonf/otolib/Godeps/_workspace/src/github.com/go-fsnotify/fsnotify"
)

// ----------------------------------------------------------------------------

// Gonf implements the Gonfer interface
type Gonf struct {
	// Config file's path
	path string
	// Config file's directory's path
	dirPath string
	// Config file
	file *os.File
	// Raw JSON config read from file
	conf map[string]interface{}
	// Avoids races when reloading config file
	confLock sync.RWMutex
	// Config file watcher
	watcher *fsnotify.Watcher

	// Callbacks mapping for each supported HTTP method
	methodMap map[string]rest.HandlerFunc
	// List of generated meta REST routes
	metaRoutes []route
	// List of generated config REST routes
	configRoutes []route
	// Global routing handler
	handler rest.ResourceHandler

	// Basic auth middleware
	basicWare *rest.AuthBasicMiddleware
	// Basic auth credentials
	authUser, authPassword string
	// Use basic auth for otogonf meta API
	// This doesn't affect basic auth endpoints specified in the config file
	// Defaults to `false`
	metaBasicAuth bool

	// Watch config file via OS notifications
	// Defaults to `false`
	watchFile bool
}

// ----------------------------------------------------------------------------

// NewGonf returns a Gonf instance that can be used to handle a config file
// meta and config API are generated for this new instance
func NewGonf(path, authUser, authPassword string) (*Gonf, error) {
	path = filepath.Clean(path)
	dirPath := filepath.Dir(path)
	f, err := os.OpenFile(path, os.O_RDWR, 0666)
	if err != nil {
		return nil, err
	}

	w, err := fsnotify.NewWatcher()
	if err != nil {
		f.Close()
		return nil, err
	}

	g := &Gonf{
		path:    path,
		dirPath: dirPath,
		file:    f,
		watcher: w,

		authUser:      authUser,
		authPassword:  authPassword,
		metaBasicAuth: false,

		watchFile: false,
	}

	g.basicWare = &rest.AuthBasicMiddleware{
		Realm: "otogonf",
		Authenticator: func(u, p string) bool {
			if u == g.authUser && p == g.authPassword {
				return true
			}
			return false
		},
	}

	g.methodMap = map[string]rest.HandlerFunc{
		"GET": g.endpointGet,
		"PUT": g.endpointSet,
	}

	g.buildMetaRoutes()
	if err := g.Load(); err != nil {
		return nil, err
	}
	if err := g.setRoutes(g.metaRoutes, g.configRoutes); err != nil {
		return nil, err
	}

	return g, nil
}

// ListenAndServe starts an HTTP server listening on addr
// It never returns, except on error, and as such should be used as a goroutine
// If the server crashes, error will be sent on errChan if != nil
func (g *Gonf) ListenAndServe(addr string, errChan chan error) {
	err := http.ListenAndServe(addr, &g.handler)

	if err != nil && errChan != nil {
		errChan <- err
	}
}

// Close destroys the Gonf object
// Once closed, a Gonf cannot be reused: build a new one
func (g *Gonf) Close() {
	if err := g.file.Close(); err != nil {
		log.Printf("%v\n")
	}
	if err := g.watcher.Close(); err != nil {
		log.Printf("%v\n")
	}
	g.watchFile = false
}

// ----------------------------------------------------------------------------

// setRoutes sets the routes given in routeLists
func (g *Gonf) setRoutes(routeLists ...[]route) error {
	routes := []*rest.Route{}

	for _, rl := range routeLists {
		for _, r := range rl {
			route := rest.Route{}
			if r.Auth {
				route = rest.Route{
					HttpMethod: r.Method,
					PathExp:    r.URL,
					Func:       g.basicWare.MiddlewareFunc(r.callback),
				}
			} else {
				route = rest.Route{
					HttpMethod: r.Method,
					PathExp:    r.URL,
					Func:       r.callback,
				}
			}
			routes = append(routes, &route)
		}
	}

	if err := g.handler.SetRoutes(routes...); err != nil {
		return err
	}

	return nil
}

// buildMetaRoutes builds meta API's routes
func (g *Gonf) buildMetaRoutes() {
	g.metaRoutes = []route{
		route{
			URL:      "/meta/routes",
			Method:   "GET",
			Auth:     g.metaBasicAuth,
			callback: g.endpointRoutes,
		},
	}
}

// ----------------------------------------------------------------------------

// MetaBasicAuth gets the basic auth setting for otogonf meta API
func (g *Gonf) MetaBasicAuth() bool {
	return g.metaBasicAuth
}

// EnableMetaBasicAuth enables basic auth for meta API and sets credentials
func (g *Gonf) EnableMetaBasicAuth() error {
	if g.metaBasicAuth {
		return nil
	}

	g.metaBasicAuth = true

	g.buildMetaRoutes()
	if err := g.setRoutes(g.metaRoutes, g.configRoutes); err != nil {
		return err
	}

	return nil
}

// DisableMetaBasicAuth disables basic auth for meta API
func (g *Gonf) DisableMetaBasicAuth() error {
	if !g.metaBasicAuth {
		return nil
	}

	g.metaBasicAuth = false

	g.buildMetaRoutes()
	if err := g.setRoutes(g.metaRoutes, g.configRoutes); err != nil {
		return err
	}

	return nil
}

// WatchFile gets the watch file setting
func (g *Gonf) WatchFile() bool {
	return g.watchFile
}

// EnableWatchFile enables watching FS notifications for this config file
// The conf API will be updated automatically if the file is modified
//
// NOTE: Due to some issues between FS notifications and the way some text
// editors write to files, the whole directory containing the config file is
// being watched instead of the file only. However, only the changes to the
// relevant file are taken into account
func (g *Gonf) EnableWatchFile() error {
	if err := g.watcher.Add(g.dirPath); err != nil {
		return err
	}

	g.watchFile = true
	go func() {
		for g.watchFile {
			select {
			case event := <-g.watcher.Events:
				if (event.Op&fsnotify.Write == fsnotify.Write ||
					event.Op&fsnotify.Rename == fsnotify.Rename ||
					event.Op&fsnotify.Chmod == fsnotify.Chmod) &&
					event.Name == g.path {
					if err := g.Load(); err != nil {
						log.Printf("WatchFile reload error: %v\n", err)
					}
				}
			case err := <-g.watcher.Errors:
				log.Printf("WatchFile error: %v\n", err)
			}
		}
	}()

	return nil
}

// DisableWatchFile disables watching fs notifications for this config file
// The conf API will be not be updated automatically if the file is modified
func (g *Gonf) DisableWatchFile() error {
	err := g.watcher.Remove(g.path)
	if err != nil {
		return err
	}

	g.watchFile = false

	return nil
}

// ----------------------------------------------------------------------------

// load implements the recursive part of Load
func (g *Gonf) load(cfg map[string]interface{}, urlAcc []string, flagsAcc []otoFlag) error {
	if err := legalOtoFlags(flagsAcc); err != nil {
		return err
	}

	for key, v := range cfg {
		k := otoFlag(key)
		if m, ok := v.(map[string]interface{}); ok {
			var err error
			if isOtoFlag(k) {
				err = g.load(m, urlAcc, append(flagsAcc, k))
			} else {
				err = g.load(m, append(urlAcc, string(k)), flagsAcc)
			}

			if err != nil {
				return err
			}
		} else if !isOtoFlag(k) {
			routes := buildRoutes(append(urlAcc, string(k)), flagsAcc, g.methodMap)
			g.configRoutes = append(g.configRoutes, routes...)
		}
	}

	return nil
}

// Load (re)loads the config from the file specified in g.path
// It is called automatically when you call NewGonf
func (g *Gonf) Load() error {
	b, err := ioutil.ReadFile(g.path)
	if err != nil {
		return err
	}

	cfg := map[string]interface{}{}
	if err := json.Unmarshal(b, &cfg); err != nil {
		return err
	}

	// forbids access to Get/Set local and HTTP while reloading
	g.confLock.Lock()
	defer g.confLock.Unlock()
	g.conf = cfg

	return g.load(cfg, []string{}, []otoFlag{})
}
