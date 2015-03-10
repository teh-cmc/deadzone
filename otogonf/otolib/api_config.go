package otolib

import (
	"encoding/json"
	"fmt"
	"io/ioutil"
	"strings"
	"time"

	"github.com/teh-cmc/otogonf/otolib/Godeps/_workspace/src/github.com/ant0ine/go-json-rest/rest"
	"github.com/teh-cmc/otogonf/otolib/Godeps/_workspace/src/github.com/teh-cmc/cast"
)

// ----------------------------------------------------------------------------

// Get returns the value associated to setting
// Only child-less fields are gettable
// Otoflags must not be part of the path parameter
//	g.Get("couchbase/network/port")
// On error, or if the value cannot be found, (nil, err) is returned
func (g *Gonf) Get(setting string) (interface{}, error) {
	path := strings.Split(setting, "/")

	// forbids access to reloader while getting the conf
	g.confLock.RLock()
	defer g.confLock.RUnlock()

	rPath, err := RawPath(g.conf, path)
	if err != nil {
		return nil, fmt.Errorf("'%v' is not gettable", setting)
	}

	v := g.conf
	for _, p := range rPath[:len(rPath)-1] {
		v = v[p].(map[string]interface{})
	}

	ret, ok := v[rPath[len(rPath)-1]]
	if !ok {
		return nil, fmt.Errorf("'%v' is not extractable", setting)
	}

	return ret, nil
}

// GetUnsafe internally calls Get but discards possible errors
func (g *Gonf) GetUnsafe(setting string) interface{} {
	v, _ := g.Get(setting)

	return v
}

// GetTime internally calls Get and makes sure a time.Time is returned
// If Get fails or in case of illegal cast, (time.Time{}, err) is returned
func (g *Gonf) GetTime(setting string) (time.Time, error) {
	v, err := g.Get(setting)
	if err != nil {
		return time.Time{}, err
	}

	return cast.ToTimeE(v)
}

// GetTimeUnsafe internally calls GetTime but discards possible errors
func (g *Gonf) GetTimeUnsafe(setting string) time.Time {
	v, _ := g.GetTime(setting)

	return v
}

// GetBool internally calls Get and makes sure a bool is returned
// If Get fails or in case of illegal cast, (false, err) is returned
func (g *Gonf) GetBool(setting string) (bool, error) {
	v, err := g.Get(setting)
	if err != nil {
		return false, err
	}

	return cast.ToBoolE(v)
}

// GetBoolUnsafe internally calls GetBool but discards possible errors
func (g *Gonf) GetBoolUnsafe(setting string) bool {
	v, _ := g.GetBool(setting)

	return v
}

// GetFloat64 internally calls Get and makes sure a float64 is returned
// If Get fails or in case of illegal cast, (0.0, err) is returned
func (g *Gonf) GetFloat64(setting string) (float64, error) {
	v, err := g.Get(setting)
	if err != nil {
		return 0.0, err
	}

	return cast.ToFloat64E(v)
}

// GetFloat64Unsafe internally calls GetFloat64 but discards possible errors
func (g *Gonf) GetFloat64Unsafe(setting string) float64 {
	v, _ := g.GetFloat64(setting)

	return v
}

// GetInt internally calls Get and makes sure an int is returned
// If Get fails or in case of illegal cast, (0, err) is returned
func (g *Gonf) GetInt(setting string) (int, error) {
	v, err := g.Get(setting)
	if err != nil {
		return 0, err
	}

	return cast.ToIntE(v)
}

// GetIntUnsafe internally calls GetInt but discards possible errors
func (g *Gonf) GetIntUnsafe(setting string) int {
	v, _ := g.GetInt(setting)

	return v
}

// GetUint internally calls Get and makes sure an uint is returned
// If Get fails or in case of illegal cast, (0, err) is returned
func (g *Gonf) GetUint(setting string) (uint, error) {
	v, err := g.Get(setting)
	if err != nil {
		return 0, err
	}

	return cast.ToUintE(v)
}

// GetUintUnsafe internally calls GetUint but discards possible errors
func (g *Gonf) GetUintUnsafe(setting string) uint {
	v, _ := g.GetUint(setting)

	return v
}

// GetString internally calls Get and makes sure a string is returned
// If Get fails or in case of illegal cast, ("", err) is returned
func (g *Gonf) GetString(setting string) (string, error) {
	v, err := g.Get(setting)
	if err != nil {
		return "", err
	}

	return cast.ToStringE(v)
}

// GetStringUnsafe internally calls GetString but discards possible errors
func (g *Gonf) GetStringUnsafe(setting string) string {
	v, _ := g.GetString(setting)

	return v
}

// GetSlice internally calls Get and makes sure a slice is returned
// If Get fails or in case of illegal cast, ([]interface{}{}, err) is returned
func (g *Gonf) GetSlice(setting string) ([]interface{}, error) {
	v, err := g.Get(setting)
	if err != nil {
		return []interface{}{}, err
	}

	return cast.ToSliceE(v)
}

// GetSliceUnsafe internally calls GetSlice but discards possible errors
func (g *Gonf) GetSliceUnsafe(setting string) []interface{} {
	v, _ := g.GetSlice(setting)

	return v
}

// GetTimeSlice internally calls Get and makes sure a []time.Time is returned
// If Get fails or in case of illegal cast, ([]time.Time{}, err) is returned
func (g *Gonf) GetTimeSlice(setting string) ([]time.Time, error) {
	v, err := g.Get(setting)
	if err != nil {
		return []time.Time{}, err
	}

	return cast.ToTimeSliceE(v)
}

// GetTimeSliceUnsafe internally calls GetTimeSlice but discards possible errors
func (g *Gonf) GetTimeSliceUnsafe(setting string) []time.Time {
	v, _ := g.GetTimeSlice(setting)

	return v
}

// GetBoolSlice internally calls Get and makes sure a []bool is returned
// If Get fails or in case of illegal cast, ([]bool{}, err) is returned
func (g *Gonf) GetBoolSlice(setting string) ([]bool, error) {
	v, err := g.Get(setting)
	if err != nil {
		return []bool{}, err
	}

	return cast.ToBoolSliceE(v)
}

// GetBoolSliceUnsafe internally calls GetBoolSlice but discards possible errors
func (g *Gonf) GetBoolSliceUnsafe(setting string) []bool {
	v, _ := g.GetBoolSlice(setting)

	return v
}

// GetFloat64Slice internally calls Get and makes sure a []float64 is returned
// If Get fails or in case of illegal cast, ([]float64{}, err) is returned
func (g *Gonf) GetFloat64Slice(setting string) ([]float64, error) {
	v, err := g.Get(setting)
	if err != nil {
		return []float64{}, err
	}

	return cast.ToFloat64SliceE(v)
}

// GetFloat64SliceUnsafe internally calls GetFloat64Slice but discards possible errors
func (g *Gonf) GetFloat64SliceUnsafe(setting string) []float64 {
	v, _ := g.GetFloat64Slice(setting)

	return v
}

// GetIntSlice internally calls Get and makes sure a []int is returned
// If Get fails or in case of illegal cast, ([]int{}, err) is returned
func (g *Gonf) GetIntSlice(setting string) ([]int, error) {
	v, err := g.Get(setting)
	if err != nil {
		return []int{}, err
	}

	return cast.ToIntSliceE(v)
}

// GetIntSliceUnsafe internally calls GetIntSlice but discards possible errors
func (g *Gonf) GetIntSliceUnsafe(setting string) []int {
	v, _ := g.GetIntSlice(setting)

	return v
}

// GetUintSlice internally calls Get and makes sure a []uint is returned
// If Get fails or in case of illegal cast, ([]uint{}, err) is returned
func (g *Gonf) GetUintSlice(setting string) ([]uint, error) {
	v, err := g.Get(setting)
	if err != nil {
		return []uint{}, err
	}

	return cast.ToUintSliceE(v)
}

// GetUintSliceUnsafe internally calls GetUintSlice but discards possible errors
func (g *Gonf) GetUintSliceUnsafe(setting string) []uint {
	v, _ := g.GetUintSlice(setting)

	return v
}

// GetStringSlice internally calls Get and makes sure a []string is returned
// If Get fails or in case of illegal cast, ([]string{}, err) is returned
func (g *Gonf) GetStringSlice(setting string) ([]string, error) {
	v, err := g.Get(setting)
	if err != nil {
		return []string{}, err
	}

	return cast.ToStringSliceE(v)
}

// GetStringSliceUnsafe internally calls GetStringSlice but discards possible errors
func (g *Gonf) GetStringSliceUnsafe(setting string) []string {
	v, _ := g.GetStringSlice(setting)

	return v
}

// endpointGet is a HTTP endpoint for Get
func (g *Gonf) endpointGet(w rest.ResponseWriter, r *rest.Request) {
	path := string(gRoutePrefixRegex.ReplaceAll([]byte(r.Request.URL.Path), []byte{}))

	v, err := g.Get(path)
	if err != nil {
		rest.Error(w, err.Error(), 400)
	} else {
		w.WriteJson(v)
	}
}

// ----------------------------------------------------------------------------

// Set returns the value associated to setting
// Only child-less fields are settable
// Otoflags must not be part of the path parameter
//	g.Set("couchbase/network/port", 8091)
func (g *Gonf) Set(setting string, value interface{}) error {
	path := strings.Split(setting, "/")

	// forbids access to reloader while setting the conf
	g.confLock.Lock()
	defer g.confLock.Unlock()
	rPath, err := RawPath(g.conf, path)
	if err != nil {
		return fmt.Errorf("'%v' is not settable", setting)
	}

	v := g.conf
	for _, p := range rPath[:len(rPath)-1] {
		v = v[p].(map[string]interface{})
	}

	oldValue := v[rPath[len(rPath)-1]]
	v[rPath[len(rPath)-1]] = value
	conf, err := json.MarshalIndent(g.conf, "", "    ")
	if err != nil {
		return err
	}

	if err := ioutil.WriteFile(g.path, conf, 0664); err != nil {
		v[rPath[len(rPath)-1]] = oldValue
		return err
	}

	return nil
}

// endpointSet is a HTTP endpoint for Set
func (g *Gonf) endpointSet(w rest.ResponseWriter, r *rest.Request) {
	path := string(gRoutePrefixRegex.ReplaceAll([]byte(r.Request.URL.Path), []byte{}))

	var v interface{}
	if err := r.DecodeJsonPayload(&v); err != nil {
		rest.Error(w, err.Error(), 400)
		return
	}

	err := g.Set(path, v)
	if err != nil {
		rest.Error(w, err.Error(), 400)
	} else {
		w.WriteJson(
			map[string]string{
				"Success": fmt.Sprintf("%v was successfully set to %v"),
			},
		)
	}
}
