package otolib

import (
	"fmt"
	"strings"
)

// otoFlag is an enum representing the different flags available in your conf
type otoFlag string

const (
	eRDOnly    otoFlag = "OTO-RDONLY"    // read only key
	eWROnly    otoFlag = "OTO-WRONLY"    // write only key
	ePrivate   otoFlag = "OTO-PRIVATE"   // private key (no API endpoint)
	eBasicAuth otoFlag = "OTO-BASICAUTH" // basic-auth required key

)

var (
	// gOtoFlags is a global mapping of every available flags
	gOtoFlags = map[otoFlag]struct{}{
		eRDOnly:    struct{}{},
		eWROnly:    struct{}{},
		ePrivate:   struct{}{},
		eBasicAuth: struct{}{},
	}
)

// ----------------------------------------------------------------------------

// legalOtoFlags returns true if the slice of flags is legal
func legalOtoFlags(flags []otoFlag) error {
	flagsMap := map[otoFlag]int{
		eRDOnly:    0,
		eWROnly:    0,
		ePrivate:   0,
		eBasicAuth: 0,
	}
	for _, f := range flags {
		flagsMap[f]++
		if flagsMap[f] > 1 {
			return fmt.Errorf("invalid config: %v was set more than once", f)
		}
	}

	if flagsMap[eRDOnly] > 0 && flagsMap[eWROnly] > 0 {
		return fmt.Errorf("invalid config: cannot use RDONLY and WRONLY together")
	}

	return nil
}

// isOtoFlag returns true if flag is an otoFlag
func isOtoFlag(flag otoFlag) bool {
	_, ok := gOtoFlags[flag]

	return ok
}

// ----------------------------------------------------------------------------

// rawPath implements the recursive part of RawPath
func rawPath(conf interface{}, path, rPath []string) ([]string, error) {
	if len(path) == 0 {
		if _, ok := conf.(map[string]interface{}); ok {
			return nil, fmt.Errorf("not a child-less field")
		}
		return rPath, nil
	}
	if _, ok := conf.(map[string]interface{}); !ok {
		return nil, nil
	}

	c := conf.(map[string]interface{})

	// this key is gettable directly
	value, ok := c[path[0]]
	if ok {
		return rawPath(value, path[1:], append(rPath, path[0]))
	}

	// this key is wrapped in otoflags
	// recursively walks through the map
	for k, v := range c {
		if isOtoFlag(otoFlag(k)) {
			value, err := rawPath(v, path, append(rPath, k))
			if value != nil || err != nil {
				return value, err
			}
		}
	}

	return nil, nil
}

// RawPath returns the real path for path, including the otoflags
// Path must point to a child-less field
func RawPath(conf interface{}, path []string) ([]string, error) {
	rp, err := rawPath(conf, path, make([]string, 0, len(path)*2))
	if err != nil {
		return nil, fmt.Errorf("'%v' is not child-less field", strings.Join(path, ""))
	}

	return rp, nil
}
