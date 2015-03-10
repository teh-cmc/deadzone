package otolib

// ----------------------------------------------------------------------------

// IsStringInSlice returns true if str exists in slice
func IsStringInSlice(slice []string, str string) bool {
	for _, s := range slice {
		if str == s {
			return true
		}
	}

	return false
}
