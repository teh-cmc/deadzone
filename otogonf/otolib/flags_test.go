package otolib

import "fmt"

// ----------------------------------------------------------------------------

var (
	gFlagged = map[string]interface{}{
		"OTO-RDONLY": map[string]interface{}{
			"OTO-BASICAUTH": map[string]interface{}{
				"elasticsearch": map[string]interface{}{
					"ip":       "127.0.0.1",
					"user":     "mark",
					"password": "knopfler",
				},
			},
		},
		"OTO-BASICAUTH": map[string]interface{}{
			"couchbase": map[string]interface{}{
				"default": map[string]interface{}{
					"ip":   "172.17.0.1",
					"port": "8091",
					"OTO-RDONLY": map[string]interface{}{
						"user": "dennis",
					},
					"OTO-WRONLY": map[string]interface{}{
						"password": "ritchie",
					},
				},
			},
		},
		"OTO-WRONLY": map[string]interface{}{
			"pgsql": map[string]interface{}{
				"username": "gregory",
				"OTO-PRIVATE": map[string]interface{}{
					"password": "house",
				},
			},
		},
	}
)

// ----------------------------------------------------------------------------

func ExampleRawPath_legal() {
	esPath, _ := RawPath(gFlagged, []string{"elasticsearch", "ip"})
	cbPath, _ := RawPath(gFlagged, []string{"couchbase", "default", "password"})
	pgPath, _ := RawPath(gFlagged, []string{"pgsql", "username"})
	pgpPath, _ := RawPath(gFlagged, []string{"pgsql", "password"})

	fmt.Printf("%v\n%v\n%v\n%v\n", esPath, cbPath, pgPath, pgpPath)

	// Output:
	// [OTO-RDONLY OTO-BASICAUTH elasticsearch ip]
	// [OTO-BASICAUTH couchbase default OTO-WRONLY password]
	// [OTO-WRONLY pgsql username]
	// [OTO-WRONLY pgsql OTO-PRIVATE password]
}

func ExampleRawPath_illegal() {
	cbPath, err := RawPath(gFlagged, []string{"couchbase"})

	fmt.Printf("%#v\n%v\n", cbPath, err)

	// Output:
	// []string(nil)
	// 'couchbase' is not child-less field
}
