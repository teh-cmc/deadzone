package otolib

import "time"

// ----------------------------------------------------------------------------

// Gonfer interface provides everything needed to handle a config file
type Gonfer interface {
	Load() error
	ListenAndServe(addr string, errChan chan error)
	Close()

	MetaBasicAuth() bool
	EnableMetaBasicAuth() error
	DisableMetaBasicAuth() error

	WatchFile() bool
	EnableWatchFile() error
	DisableWatchFile() error

	Routes() []route

	Get(setting string) (interface{}, error)
	GetUnsafe(setting string) interface{}
	GetTime(setting string) (time.Time, error)
	GetTimeUnsafe(setting string) time.Time
	GetBool(setting string) (bool, error)
	GetBoolUnsafe(setting string) bool
	GetFloat64(setting string) (float64, error)
	GetFloat64Unsafe(setting string) float64
	GetInt(setting string) (int, error)
	GetIntUnsafe(setting string) int
	GetUint(setting string) (uint, error)
	GetUintUnsafe(setting string) uint
	GetString(setting string) (string, error)
	GetStringUnsafe(setting string) string

	GetSlice(setting string) ([]interface{}, error)
	GetSliceUnsafe(setting string) []interface{}
	GetTimeSlice(setting string) ([]time.Time, error)
	GetTimeSliceUnsafe(setting string) []time.Time
	GetBoolSlice(setting string) ([]bool, error)
	GetBoolSliceUnsafe(setting string) []bool
	GetFloat64Slice(setting string) ([]float64, error)
	GetFloat64SliceUnsafe(setting string) []float64
	GetIntSlice(setting string) ([]int, error)
	GetIntSliceUnsafe(setting string) []int
	GetUintSlice(setting string) ([]uint, error)
	GetUintSliceUnsafe(setting string) []uint
	GetStringSlice(setting string) ([]string, error)
	GetStringSliceUnsafe(setting string) []string

	Set(setting string, value interface{}) error
}
