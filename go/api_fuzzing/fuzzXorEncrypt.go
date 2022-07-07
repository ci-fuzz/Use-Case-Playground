package api_fuzzing

import "encoding/binary"

func encrypt(n uint64) uint64 {
	return n ^ 0x1122334455667788
}

func FuzzXorEncrypt(data []byte) int {
	if len(data) < 16 {
		return 0
	}
	n := binary.BigEndian.Uint64(data[:8])
	n2 := binary.BigEndian.Uint64(data[8:16])

	if encrypt(n) == 5788627691251634856 && encrypt(n2) == 6293579535917519017 {
		panic("XOR with a constant is not a secure encryption ;-)")
	}
	return 0
}
