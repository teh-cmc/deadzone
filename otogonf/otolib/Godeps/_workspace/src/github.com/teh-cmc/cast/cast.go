// Copyright © 2014 Steve Francia <spf@spf13.com>.
// Copyright © 2014 Clement 'cmc' Rey <cr.rey.clement@gmail.com>.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

package cast

import "time"

// -----------------------------------------------------------------------------

func ToBool(i interface{}) bool {
	v, _ := ToBoolE(i)
	return v
}

func ToTime(i interface{}) time.Time {
	v, _ := ToTimeE(i)
	return v
}

func ToFloat64(i interface{}) float64 {
	v, _ := ToFloat64E(i)
	return v
}

func ToInt(i interface{}) int {
	v, _ := ToIntE(i)
	return v
}

func ToUint(i interface{}) uint {
	v, _ := ToUintE(i)
	return v
}

func ToString(i interface{}) string {
	v, _ := ToStringE(i)
	return v
}

// -----------------------------------------------------------------------------

func ToSlice(i interface{}) []interface{} {
	v, _ := ToSliceE(i)
	return v
}

func ToBoolSlice(i interface{}) []bool {
	v, _ := ToBoolSliceE(i)
	return v
}

func ToTimeSlice(i interface{}) []time.Time {
	v, _ := ToTimeSliceE(i)
	return v
}

func ToFloat64Slice(i interface{}) []float64 {
	v, _ := ToFloat64SliceE(i)
	return v
}

func ToIntSlice(i interface{}) []int {
	v, _ := ToIntSliceE(i)
	return v
}

func ToUintSlice(i interface{}) []uint {
	v, _ := ToUintSliceE(i)
	return v
}

func ToStringSlice(i interface{}) []string {
	v, _ := ToStringSliceE(i)
	return v
}

// -----------------------------------------------------------------------------

func ToStringMapString(i interface{}) map[string]string {
	v, _ := ToStringMapStringE(i)
	return v
}

func ToStringMap(i interface{}) map[string]interface{} {
	v, _ := ToStringMapE(i)
	return v
}
