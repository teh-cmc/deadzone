// Copyright © 2015 Clement 'cmc' Rey <cr.rey.clement@gmail.com>.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

package gohotconf

import (
	"encoding/json"
	"io/ioutil"
	"log"
	"path/filepath"
	"sync"

	"gopkg.in/fsnotify.v1"
)

// ----------------------------------------------------------------------------

// Config represents a JSON-esque config file
type Config struct {
	path    string
	dirPath string

	conf map[string]interface{}
	// prevents races when reloading config file
	confLock sync.RWMutex

	watcher *fsnotify.Watcher
}

// ----------------------------------------------------------------------------

// NewConfig returns a freshly built Config
func NewConfig(path string) (*Config, error) {
	path = filepath.Clean(path)
	dirPath := filepath.Dir(path)

	w, err := fsnotify.NewWatcher()
	if err != nil {
		return nil, err
	}

	c := &Config{
		path:    path,
		dirPath: dirPath,

		watcher: w,
	}

	if err := c.Reload(); err != nil {
		c.Close()
		return nil, err
	}

	return c, nil
}

// Close kills the Config instance properly
func (c *Config) Close() {
	if c.watcher != nil {
		if err := c.watcher.Close(); err != nil {
			log.Println(err)
		}
	}
}

// ----------------------------------------------------------------------------

// StartWatching starts watching FS notifications for this config file
//
// File updates are pushed on the returned *Diff chan every time they happen
//
// NOTE: Due to the various hacky ways some text editors may write to files,
// the whole directory containing the config file has to be watched instead
// of just the only file.
// For the same reasons, we're not only looking for write events.
func (c *Config) StartWatching() (<-chan *Diff, error) {
	if err := c.Reload(); err != nil {
		return nil, err
	}
	if err := c.watcher.Add(c.dirPath); err != nil {
		return nil, err
	}

	// infinite *Diff chan generator
	diffChan := make(chan *Diff)

	go func() {
		for {
			select {
			case event, ok := <-c.watcher.Events:
				if !ok {
					// the watcher is closed, kill the goroutine
					close(diffChan)
					return
				}
				if (event.Op&fsnotify.Write == fsnotify.Write ||
					event.Op&fsnotify.Rename == fsnotify.Rename ||
					event.Op&fsnotify.Chmod == fsnotify.Chmod) &&
					event.Name == c.path {
					oldConf := c.GetConfig()
					if err := c.Reload(); err != nil {
						log.Printf("file reloading failed: %v\n", err)
					}
					diffChan <- NewDiff(oldConf, c.GetConfig())
				}
			case err, ok := <-c.watcher.Errors:
				if ok {
					// ignored, just a reminder
					log.Printf("file watching error: %v\n", err)
				}
			}
		}
	}()

	return diffChan, nil
}

// StopWatching stops watching FS notifications for this config file
func (c *Config) StopWatching() error {
	err := c.watcher.Remove(c.path)

	return err
}

// ----------------------------------------------------------------------------

// Reload reloads the config specified by `c.path`
func (c *Config) Reload() error {
	b, err := ioutil.ReadFile(c.path)
	if err != nil {
		return err
	}

	cfg := map[string]interface{}{}
	if err := json.Unmarshal(b, &cfg); err != nil {
		return err
	}

	// updates current conf race-free
	c.confLock.Lock()
	c.conf = cfg
	c.confLock.Unlock()

	return nil
}

// ----------------------------------------------------------------------------

// GetConfig returns a copy of the actual configuration
//
// use this if you want to map the configuration to a structure
// (via `github.com/fatih/structs` for example)
func (c *Config) GetConfig() map[string]interface{} {
	c.confLock.RLock()
	defer c.confLock.RUnlock()

	return c.conf
}
