package otolib

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"net/http"
	"net/http/httptest"
	"strings"
	"testing"
	"time"
)

// ----------------------------------------------------------------------------

func TestGonf_Routes(t *testing.T) {
	g, err := NewGonf("./samples/valid_conf.json", "alain", "souchon")
	if err != nil {
		t.Error(err)
	}

	for _, r := range g.Routes() {
		if !((r.URL == "/meta/routes" && r.Method == "GET" && r.Auth == false) ||
			(r.URL == "/config/pgsql/username" && r.Method == "PUT" && r.Auth == false) ||
			(r.URL == "/config/elasticsearch/ip" && r.Method == "GET" && r.Auth == true) ||
			(r.URL == "/config/elasticsearch/user" && r.Method == "GET" && r.Auth == true) ||
			(r.URL == "/config/elasticsearch/password" && r.Method == "GET" && r.Auth == true) ||
			(r.URL == "/config/couchbase/default/user" && r.Method == "GET" && r.Auth == true) ||
			(r.URL == "/config/couchbase/default/password" && r.Method == "PUT" && r.Auth == true) ||
			(r.URL == "/config/couchbase/default/ip" && r.Method == "GET" && r.Auth == true) ||
			(r.URL == "/config/couchbase/default/ip" && r.Method == "PUT" && r.Auth == true) ||
			(r.URL == "/config/couchbase/default/port" && r.Method == "GET" && r.Auth == true) ||
			(r.URL == "/config/couchbase/default/port" && r.Method == "PUT" && r.Auth == true)) {
			t.Errorf("%v should not exist", r)
		}
	}

	g.Close()
}

func TestGonf_Routes_HTTP(t *testing.T) {
	g, err := NewGonf("./samples/valid_conf.json", "robert", "plant")
	if err != nil {
		t.Error(err)
	}

	s := httptest.NewServer(&g.handler)
	resp, err := http.Get(fmt.Sprintf("%s/meta/routes", s.URL))
	if err != nil {
		t.Error(err)
	}
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		t.Error(err)
	}

	var routes []route
	err = json.Unmarshal(body, &routes)
	if err != nil {
		t.Error(err)
	}

	for _, r := range routes {
		if !((r.URL == "/meta/routes" && r.Method == "GET" && r.Auth == false) ||
			(r.URL == "/config/pgsql/username" && r.Method == "PUT" && r.Auth == false) ||
			(r.URL == "/config/elasticsearch/ip" && r.Method == "GET" && r.Auth == true) ||
			(r.URL == "/config/elasticsearch/user" && r.Method == "GET" && r.Auth == true) ||
			(r.URL == "/config/elasticsearch/password" && r.Method == "GET" && r.Auth == true) ||
			(r.URL == "/config/couchbase/default/user" && r.Method == "GET" && r.Auth == true) ||
			(r.URL == "/config/couchbase/default/password" && r.Method == "PUT" && r.Auth == true) ||
			(r.URL == "/config/couchbase/default/ip" && r.Method == "GET" && r.Auth == true) ||
			(r.URL == "/config/couchbase/default/ip" && r.Method == "PUT" && r.Auth == true) ||
			(r.URL == "/config/couchbase/default/port" && r.Method == "GET" && r.Auth == true) ||
			(r.URL == "/config/couchbase/default/port" && r.Method == "PUT" && r.Auth == true)) {
			t.Errorf("%v should not exist", r)
		}
	}

	s.Close()
	g.Close()
}

// ----------------------------------------------------------------------------

func ExampleGonf_Get_legal() {
	g, err := NewGonf("./samples/valid_conf.json", "arnold", "schwarzenegger")
	if err != nil {
		fmt.Printf("%v\n", err)
	}

	esIP, _ := g.Get("elasticsearch/ip")
	cbPw, _ := g.Get("couchbase/default/password")
	pgUser, _ := g.Get("pgsql/username")
	pgPassword, _ := g.Get("pgsql/password")

	fmt.Printf("%v\n%v\n%v\n%v\n", esIP, cbPw, pgUser, pgPassword)

	g.Close()

	// Output:
	// 127.0.0.1
	// ritchie
	// gregory
	// house
}

func ExampleGonf_Get_illegal() {
	g, err := NewGonf("./samples/valid_conf.json", "brian", "kernighan")
	if err != nil {
		fmt.Printf("%v\n", err)
	}

	cb, err := g.Get("couchbase")

	fmt.Printf("%v\n%v\n", cb, err)

	g.Close()

	// Output:
	// <nil>
	// 'couchbase' is not gettable
}

// ----------------------------------------------------------------------------

func ExampleGonf_Set_legal() {
	g, err := NewGonf("./samples/valid_conf.json", "david", "gilmour")
	if err != nil {
		fmt.Printf("%v\n", err)
	}

	g.Set("elasticsearch/ip", "192.0.0.42")
	g.Set("couchbase/default/password", "eihctir")
	g.Set("pgsql/username", "donald")
	g.Set("pgsql/password", "knuth")

	g.Load()

	esIP, _ := g.Get("elasticsearch/ip")
	cbPw, _ := g.Get("couchbase/default/password")
	pgUser, _ := g.Get("pgsql/username")
	pgPassword, _ := g.Get("pgsql/password")

	fmt.Printf("%v\n%v\n%v\n%v\n", esIP, cbPw, pgUser, pgPassword)

	g.Set("elasticsearch/ip", "127.0.0.1")
	g.Set("couchbase/default/password", "ritchie")
	g.Set("pgsql/username", "gregory")
	g.Set("pgsql/password", "house")

	g.Load()

	esIP, _ = g.Get("elasticsearch/ip")
	cbPw, _ = g.Get("couchbase/default/password")
	pgUser, _ = g.Get("pgsql/username")
	pgPassword, _ = g.Get("pgsql/password")

	fmt.Printf("%v\n%v\n%v\n%v\n", esIP, cbPw, pgUser, pgPassword)

	g.Close()

	// Output:
	// 192.0.0.42
	// eihctir
	// donald
	// knuth
	// 127.0.0.1
	// ritchie
	// gregory
	// house
}

func ExampleGonf_Set_illegal() {
	g, err := NewGonf("./samples/valid_conf.json", "mike", "mccready")
	if err != nil {
		fmt.Printf("%v\n", err)
	}

	err = g.Set("couchbase", "nope")

	fmt.Printf("%v\n", err)

	g.Close()

	// Output:
	// 'couchbase' is not settable
}

// ----------------------------------------------------------------------------

func TestGonf_conf_races(t *testing.T) {
	g, err := NewGonf("./samples/valid_conf_races.json", "roger", "waters")
	if err != nil {
		t.Error(err)
	}

	c := http.Client{Timeout: time.Second * 2}
	s := httptest.NewServer(&g.handler)

	for i := 1; i < 100; i++ {
		go g.Set("ken", "thompson")
		go g.Get("ken")
		go c.Get(fmt.Sprintf("%s/config/ken", s.URL))

		d := strings.NewReader(`"thompson"`)
		r, err := http.NewRequest("PUT", fmt.Sprintf("%s/config/ken", s.URL), d)
		if err != nil {
			t.Error(err)
		}
		r.Header.Set("Content-Type", "application/json")
		c.Do(r)
	}

	time.Sleep(time.Second * 2)
}
