package rest

import (
	"github.com/teh-cmc/otogonf/otolib/Godeps/_workspace/src/github.com/ant0ine/go-json-rest/rest/test"
	"testing"
)

func TestGzipEnabled(t *testing.T) {

	handler := ResourceHandler{
		DisableJsonIndent: true,
		EnableGzip:        true,
	}
	handler.SetRoutes(
		&Route{"GET", "/ok",
			func(w ResponseWriter, r *Request) {
				w.WriteJson(map[string]string{"Id": "123"})
			},
		},
		&Route{"GET", "/error",
			func(w ResponseWriter, r *Request) {
				Error(w, "gzipped error", 500)
			},
		},
	)

	recorded := test.RunRequest(t, &handler, test.MakeSimpleRequest("GET", "http://1.2.3.4/ok", nil))
	recorded.CodeIs(200)
	recorded.ContentTypeIsJson()
	recorded.ContentEncodingIsGzip()
	recorded.HeaderIs("Vary", "Accept-Encoding")

	recorded = test.RunRequest(t, &handler, test.MakeSimpleRequest("GET", "http://1.2.3.4/error", nil))
	recorded.CodeIs(500)
	recorded.ContentTypeIsJson()
	recorded.ContentEncodingIsGzip()
	recorded.HeaderIs("Vary", "Accept-Encoding")
}

func TestGzipDisabled(t *testing.T) {

	handler := ResourceHandler{
		DisableJsonIndent: true,
	}
	handler.SetRoutes(
		&Route{"GET", "/ok",
			func(w ResponseWriter, r *Request) {
				w.WriteJson(map[string]string{"Id": "123"})
			},
		},
	)

	recorded := test.RunRequest(t, &handler, test.MakeSimpleRequest("GET", "http://1.2.3.4/ok", nil))
	recorded.CodeIs(200)
	recorded.ContentTypeIsJson()
	recorded.HeaderIs("Content-Encoding", "")
	recorded.HeaderIs("Vary", "")
}
