package otolib

import (
	"log"
	"regexp"
	"strings"

	"github.com/teh-cmc/otogonf/otolib/Godeps/_workspace/src/github.com/ant0ine/go-json-rest/rest"
)

// ----------------------------------------------------------------------------

const (
	// prefixed to every generated route
	gRoutePrefix = "/config/"
)

var (
	// regex to remove prefix and extra slashes
	gRoutePrefixRegex = regexp.MustCompile(`^/+config/+`)
)

// route represents a generated HTTP route and its specs
type route struct {
	// URL
	URL string
	// HTTP method
	Method string
	// Basic-auth required
	Auth bool
	// Callback
	callback rest.HandlerFunc
}

// ----------------------------------------------------------------------------

// buildRoutes returns a list of routes matching the selected flags
func buildRoutes(urlAcc []string, flagsAcc []otoFlag, methodMap map[string]rest.HandlerFunc) []route {
	flags := map[otoFlag]struct{}{}
	methods := map[string]bool{
		"GET": true,
		"PUT": true,
	}

	url := gRoutePrefix + strings.Join(urlAcc, "/")
	for _, f := range flagsAcc {
		flags[f] = struct{}{}
	}
	_, auth := flags[eBasicAuth]
	_, rdOnly := flags[eRDOnly]
	_, wrOnly := flags[eWROnly]
	_, private := flags[ePrivate]

	if private {
		return []route{}
	}
	if rdOnly {
		methods["PUT"] = false
	} else if wrOnly {
		methods["GET"] = false
	}

	routes := []route{}
	r := route{}
	for m, e := range methods {
		if e {
			f, ok := methodMap[m]
			if !ok {
				log.Printf("warning: no function available to handle %v method (%v)", m, url)
			} else {
				r = route{
					URL:      url,
					Method:   m,
					Auth:     auth,
					callback: f,
				}
				routes = append(routes, r)
			}
		}
	}

	return routes
}
