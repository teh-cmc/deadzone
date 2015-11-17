// Copyright © 2014 Steve Francia <spf@spf13.com>.
// Copyright © 2014 Clement 'cmc' Rey <cr.rey.clement@gmail.com>.
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file.

package cast

import (
	"errors"
	"fmt"
	"reflect"
	"strconv"
	"time"
)

// -----------------------------------------------------------------------------

func ToTimeE(i interface{}) (tim time.Time, err error) {
	switch s := i.(type) {
	case time.Time:
		return s, nil
	case string:
		d, e := StringToDate(s)
		if e == nil {
			return d, nil
		}
		return time.Time{}, fmt.Errorf("Could not parse Date/Time format: %v", e)
	default:
		return time.Time{}, fmt.Errorf("Unable to Cast %#v to Time", i)
	}
}

func ToBoolE(i interface{}) (bool, error) {
	switch b := i.(type) {
	case bool:
		return b, nil
	case nil:
		return false, nil
	case int:
		if b > 0 {
			return true, nil
		}
		return false, nil
	case string:
		if b == "true" {
			return true, nil
		} else if b == "false" {
			return false, nil
		} else {
			return false, fmt.Errorf("Unable to Cast %#v to bool", i)
		}
	default:
		return false, fmt.Errorf("Unable to Cast %#v to bool", i)
	}
}

func ToFloat64E(i interface{}) (float64, error) {
	switch s := i.(type) {
	case float64:
		return s, nil
	case float32:
		return float64(s), nil
	case int64:
		return float64(s), nil
	case int32:
		return float64(s), nil
	case int16:
		return float64(s), nil
	case int8:
		return float64(s), nil
	case int:
		return float64(s), nil
	case string:
		v, err := strconv.ParseFloat(s, 64)
		if err == nil {
			return v, nil
		} else {
			return 0.0, fmt.Errorf("Unable to Cast %#v to float64", i)
		}
	default:
		return 0.0, fmt.Errorf("Unable to Cast %#v to float64", i)
	}
}

func ToIntE(i interface{}) (int, error) {
	switch s := i.(type) {
	case int:
		return s, nil
	case int64:
		return int(s), nil
	case int32:
		return int(s), nil
	case int16:
		return int(s), nil
	case int8:
		return int(s), nil
	case string:
		v, err := strconv.ParseInt(s, 0, 0)
		if err == nil {
			return int(v), nil
		} else {
			return 0, fmt.Errorf("Unable to Cast %#v to int", i)
		}
	case float64:
		return int(s), nil
	case bool:
		if s {
			return 1, nil
		} else {
			return 0, nil
		}
	case nil:
		return 0, nil
	default:
		return 0, fmt.Errorf("Unable to Cast %#v to int", i)
	}
}

func ToUintE(i interface{}) (uint, error) {
	intToUint := func(n int) (uint, error) {
		if n < 0 {
			return 0, fmt.Errorf("Unable to Cast %#v to uint", i)
		}
		return uint(n), nil
	}

	switch s := i.(type) {
	case uint:
		return s, nil
	case uint64:
		return uint(s), nil
	case uint32:
		return uint(s), nil
	case uint16:
		return uint(s), nil
	case uint8:
		return uint(s), nil
	case int:
		return intToUint(int(s))
	case int64:
		return intToUint(int(s))
	case int32:
		return intToUint(int(s))
	case int16:
		return intToUint(int(s))
	case int8:
		return intToUint(int(s))
	case string:
		v, err := strconv.ParseUint(s, 0, 0)
		if err == nil {
			return uint(v), nil
		} else {
			return 0, fmt.Errorf("Unable to Cast %#v to uint", i)
		}
	case float64:
		return intToUint(int(s))
	case bool:
		if s {
			return 1, nil
		} else {
			return 0, nil
		}
	case nil:
		return 0, nil
	default:
		return 0, fmt.Errorf("Unable to Cast %#v to uint", i)
	}
}

func ToStringE(i interface{}) (string, error) {
	switch s := i.(type) {
	case string:
		return s, nil
	case float64:
		return strconv.FormatFloat(s, 'f', -1, 64), nil
	case int:
		return strconv.FormatInt(int64(s), 10), nil
	case []byte:
		return string(s), nil
	case nil:
		return "", nil
	default:
		return "", fmt.Errorf("Unable to Cast %#v to string", i)
	}
}

// -----------------------------------------------------------------------------

func ToSliceE(i interface{}) ([]interface{}, error) {
	var s []interface{}

	switch v := i.(type) {
	case []interface{}:
		for _, u := range v {
			s = append(s, u)
		}
		return s, nil
	case []map[string]interface{}:
		for _, u := range v {
			s = append(s, u)
		}
		return s, nil
	default:
		return s, fmt.Errorf("Unable to Cast %#v of type %v to []interface{}", i, reflect.TypeOf(i))
	}

	return s, fmt.Errorf("Unable to Cast %#v to []interface{}", i)
}

func ToBoolSliceE(i interface{}) ([]bool, error) {
	var a []bool

	switch v := i.(type) {
	case []interface{}:
		for _, u := range v {
			a = append(a, ToBool(u))
		}
		return a, nil
	case []bool:
		return v, nil
	default:
		return a, fmt.Errorf("Unable to Cast %#v to []bool", i)
	}

	return a, fmt.Errorf("Unable to Cast %#v to []bool", i)
}

func ToTimeSliceE(i interface{}) ([]time.Time, error) {
	var a []time.Time

	switch v := i.(type) {
	case []interface{}:
		for _, u := range v {
			a = append(a, ToTime(u))
		}
		return a, nil
	case []time.Time:
		return v, nil
	default:
		return a, fmt.Errorf("Unable to Cast %#v to []time.Time", i)
	}

	return a, fmt.Errorf("Unable to Cast %#v to []time.Time", i)
}

func ToFloat64SliceE(i interface{}) ([]float64, error) {
	var a []float64

	switch v := i.(type) {
	case []interface{}:
		for _, u := range v {
			a = append(a, ToFloat64(u))
		}
		return a, nil
	case []float64:
		return v, nil
	default:
		return a, fmt.Errorf("Unable to Cast %#v to []float64", i)
	}

	return a, fmt.Errorf("Unable to Cast %#v to []float64", i)
}

func ToIntSliceE(i interface{}) ([]int, error) {
	var a []int

	switch v := i.(type) {
	case []interface{}:
		for _, u := range v {
			a = append(a, ToInt(u))
		}
		return a, nil
	case []int:
		return v, nil
	default:
		return a, fmt.Errorf("Unable to Cast %#v to []int", i)
	}

	return a, fmt.Errorf("Unable to Cast %#v to []int", i)
}

func ToUintSliceE(i interface{}) ([]uint, error) {
	var a []uint

	switch v := i.(type) {
	case []interface{}:
		for _, u := range v {
			a = append(a, ToUint(u))
		}
		return a, nil
	case []uint:
		return v, nil
	default:
		return a, fmt.Errorf("Unable to Cast %#v to []uint", i)
	}

	return a, fmt.Errorf("Unable to Cast %#v to []uint", i)
}

func ToStringSliceE(i interface{}) ([]string, error) {
	var a []string

	switch v := i.(type) {
	case []interface{}:
		for _, u := range v {
			a = append(a, ToString(u))
		}
		return a, nil
	case []string:
		return v, nil
	default:
		return a, fmt.Errorf("Unable to Cast %#v to []string", i)
	}

	return a, fmt.Errorf("Unable to Cast %#v to []string", i)
}

// -----------------------------------------------------------------------------

func ToStringMapStringE(i interface{}) (map[string]string, error) {
	var m = map[string]string{}

	switch v := i.(type) {
	case map[interface{}]interface{}:
		for k, val := range v {
			m[ToString(k)] = ToString(val)
		}
		return m, nil
	case map[string]interface{}:
		for k, val := range v {
			m[ToString(k)] = ToString(val)
		}
		return m, nil
	case map[string]string:
		return v, nil
	default:
		return m, fmt.Errorf("Unable to Cast %#v to map[string]string", i)
	}
	return m, fmt.Errorf("Unable to Cast %#v to map[string]string", i)
}

func ToStringMapE(i interface{}) (map[string]interface{}, error) {
	var m = map[string]interface{}{}

	switch v := i.(type) {
	case map[interface{}]interface{}:
		for k, val := range v {
			m[ToString(k)] = val
		}
		return m, nil
	case map[string]interface{}:
		return v, nil
	default:
		return m, fmt.Errorf("Unable to Cast %#v to map[string]interface{}", i)
	}

	return m, fmt.Errorf("Unable to Cast %#v to map[string]interface{}", i)
}

// -----------------------------------------------------------------------------

func StringToDate(s string) (time.Time, error) {
	return parseDateWith(s, []string{
		time.RFC3339,
		"2006-01-02T15:04:05", // iso8601 without timezone
		time.RFC1123Z,
		time.RFC1123,
		time.RFC822Z,
		time.RFC822,
		time.ANSIC,
		time.UnixDate,
		time.RubyDate,
		"2006-01-02 15:04:05Z07:00",
		"02 Jan 06 15:04 MST",
		"2006-01-02",
		"02 Jan 2006",
	})
}

func parseDateWith(s string, dates []string) (d time.Time, e error) {
	for _, dateType := range dates {
		if d, e = time.Parse(dateType, s); e == nil {
			return
		}
	}
	return d, errors.New(fmt.Sprintf("Unable to parse date: %s", s))
}
