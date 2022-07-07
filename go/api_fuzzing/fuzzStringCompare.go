package api_fuzzing

import "strings"

func FuzzStringCompare(data []byte) int {
	if len(data) < 9 {
		return 0
	}
	str1 := string(data[:8])
	str2 := string(data[8:])
	if str1 == "Awesome " && strings.Compare(str2, "Fuzzing!") == 0 {
		panic("We found a bug!")
	}
	return 0
}
