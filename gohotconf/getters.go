// Copyright © 2015 Clement 'cmc' Rey <cr.rey.clement@gmail.com>.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

package gohotconf

import (
	"fmt"
	"strings"
	"time"

	"github.com/teh-cmc/cast"
)

// ----------------------------------------------------------------------------

// Get returns the value associated with `option`, if it exists
//
// `option` is of the form path/to/option
func (c *Config) Get(option string) (interface{}, error) {
	optionSplit := strings.Split(option, "/")

	// gets current conf race-free
	c.confLock.RLock()
	v := c.conf
	c.confLock.RUnlock()
	ok := false
	for _, p := range optionSplit[:len(optionSplit)-1] {
		v, ok = v[p].(map[string]interface{})
		if !ok {
			return nil, fmt.Errorf("no such option: %v", option)
		}
	}

	ret, ok := v[optionSplit[len(optionSplit)-1]]
	if !ok {
		return nil, fmt.Errorf("no such option: %v", option)
	}

	return ret, nil
}

// GetUnsafe internally calls Get and discards possible errors
func (c *Config) GetUnsafe(setting string) interface{} {
	v, _ := c.Get(setting)

	return v
}

// GetTime internally calls Get and makes sure a time.Time is returned
func (c *Config) GetTime(setting string) (time.Time, error) {
	v, err := c.Get(setting)
	if err != nil {
		return time.Time{}, err
	}

	return cast.ToTimeE(v)
}

// GetTimeUnsafe internally calls GetTime and discards possible errors
func (c *Config) GetTimeUnsafe(setting string) time.Time {
	v, _ := c.GetTime(setting)

	return v
}

// GetBool internally calls Get and makes sure a bool is returned
func (c *Config) GetBool(setting string) (bool, error) {
	v, err := c.Get(setting)
	if err != nil {
		return false, err
	}

	return cast.ToBoolE(v)
}

// GetBoolUnsafe internally calls GetBool and discards possible errors
func (c *Config) GetBoolUnsafe(setting string) bool {
	v, _ := c.GetBool(setting)

	return v
}

// GetFloat64 internally calls Get and makes sure a float64 is returned
func (c *Config) GetFloat64(setting string) (float64, error) {
	v, err := c.Get(setting)
	if err != nil {
		return 0.0, err
	}

	return cast.ToFloat64E(v)
}

// GetFloat64Unsafe internally calls GetFloat64 and discards possible errors
func (c *Config) GetFloat64Unsafe(setting string) float64 {
	v, _ := c.GetFloat64(setting)

	return v
}

// GetInt internally calls Get and makes sure an int is returned
func (c *Config) GetInt(setting string) (int, error) {
	v, err := c.Get(setting)
	if err != nil {
		return 0, err
	}

	return cast.ToIntE(v)
}

// GetIntUnsafe internally calls GetInt and discards possible errors
func (c *Config) GetIntUnsafe(setting string) int {
	v, _ := c.GetInt(setting)

	return v
}

// GetUint internally calls Get and makes sure an uint is returned
func (c *Config) GetUint(setting string) (uint, error) {
	v, err := c.Get(setting)
	if err != nil {
		return 0, err
	}

	return cast.ToUintE(v)
}

// GetUintUnsafe internally calls GetUint and discards possible errors
func (c *Config) GetUintUnsafe(setting string) uint {
	v, _ := c.GetUint(setting)

	return v
}

// GetString internally calls Get and makes sure a string is returned
func (c *Config) GetString(setting string) (string, error) {
	v, err := c.Get(setting)
	if err != nil {
		return "", err
	}

	return cast.ToStringE(v)
}

// GetStringUnsafe internally calls GetString and discards possible errors
func (c *Config) GetStringUnsafe(setting string) string {
	v, _ := c.GetString(setting)

	return v
}

// GetSlice internally calls Get and makes sure a slice is returned
func (c *Config) GetSlice(setting string) ([]interface{}, error) {
	v, err := c.Get(setting)
	if err != nil {
		return []interface{}{}, err
	}

	return cast.ToSliceE(v)
}

// GetSliceUnsafe internally calls GetSlice and discards possible errors
func (c *Config) GetSliceUnsafe(setting string) []interface{} {
	v, _ := c.GetSlice(setting)

	return v
}

// GetTimeSlice internally calls Get and makes sure a []time.Time is returned
func (c *Config) GetTimeSlice(setting string) ([]time.Time, error) {
	v, err := c.Get(setting)
	if err != nil {
		return []time.Time{}, err
	}

	return cast.ToTimeSliceE(v)
}

// GetTimeSliceUnsafe internally calls GetTimeSlice and discards possible errors
func (c *Config) GetTimeSliceUnsafe(setting string) []time.Time {
	v, _ := c.GetTimeSlice(setting)

	return v
}

// GetBoolSlice internally calls Get and makes sure a []bool is returned
func (c *Config) GetBoolSlice(setting string) ([]bool, error) {
	v, err := c.Get(setting)
	if err != nil {
		return []bool{}, err
	}

	return cast.ToBoolSliceE(v)
}

// GetBoolSliceUnsafe internally calls GetBoolSlice and discards possible errors
func (c *Config) GetBoolSliceUnsafe(setting string) []bool {
	v, _ := c.GetBoolSlice(setting)

	return v
}

// GetFloat64Slice internally calls Get and makes sure a []float64 is returned
func (c *Config) GetFloat64Slice(setting string) ([]float64, error) {
	v, err := c.Get(setting)
	if err != nil {
		return []float64{}, err
	}

	return cast.ToFloat64SliceE(v)
}

// GetFloat64SliceUnsafe internally calls GetFloat64Slice and discards possible errors
func (c *Config) GetFloat64SliceUnsafe(setting string) []float64 {
	v, _ := c.GetFloat64Slice(setting)

	return v
}

// GetIntSlice internally calls Get and makes sure a []int is returned
func (c *Config) GetIntSlice(setting string) ([]int, error) {
	v, err := c.Get(setting)
	if err != nil {
		return []int{}, err
	}

	return cast.ToIntSliceE(v)
}

// GetIntSliceUnsafe internally calls GetIntSlice and discards possible errors
func (c *Config) GetIntSliceUnsafe(setting string) []int {
	v, _ := c.GetIntSlice(setting)

	return v
}

// GetUintSlice internally calls Get and makes sure a []uint is returned
func (c *Config) GetUintSlice(setting string) ([]uint, error) {
	v, err := c.Get(setting)
	if err != nil {
		return []uint{}, err
	}

	return cast.ToUintSliceE(v)
}

// GetUintSliceUnsafe internally calls GetUintSlice and discards possible errors
func (c *Config) GetUintSliceUnsafe(setting string) []uint {
	v, _ := c.GetUintSlice(setting)

	return v
}

// GetStringSlice internally calls Get and makes sure a []string is returned
func (c *Config) GetStringSlice(setting string) ([]string, error) {
	v, err := c.Get(setting)
	if err != nil {
		return []string{}, err
	}

	return cast.ToStringSliceE(v)
}

// GetStringSliceUnsafe internally calls GetStringSlice and discards possible errors
func (c *Config) GetStringSliceUnsafe(setting string) []string {
	v, _ := c.GetStringSlice(setting)

	return v
}
