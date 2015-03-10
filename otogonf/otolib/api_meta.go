package otolib

import "github.com/teh-cmc/otogonf/otolib/Godeps/_workspace/src/github.com/ant0ine/go-json-rest/rest"

// ----------------------------------------------------------------------------

// Routes returns the available /meta and /config routes
func (g *Gonf) Routes() []route {
	return append(g.metaRoutes, g.configRoutes...)
}

// endpointRoutes is a HTTP endpoint for Routes
func (g *Gonf) endpointRoutes(w rest.ResponseWriter, _ *rest.Request) {
	w.WriteJson(g.Routes())
}
