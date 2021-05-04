/**
Utility functions used by xhptdc8_display_info package
*/

package xhptdc8_info_display

import (
	"unsafe"
)

func convert_byte_ptr_to_string(byte_ptr *rune, dest_string *string) {
	resultStrInBytes := *(*[1024]byte)(unsafe.Pointer(byte_ptr))
	(*dest_string) = ""
	for strIndex := 0; strIndex < 1024; strIndex++ {
		if resultStrInBytes[strIndex] == 0 {
			break
		}
		(*dest_string) += string(resultStrInBytes[strIndex])
	}
}

func fixed824_to_float(fixed_val Crono_int_t) (float_val Crono_float_t) {
	// Lower 24 bit contain the number "after the point", the upper eight the rest
	float_val = (Crono_float_t)(fixed_val>>24) + ((Crono_float_t)(fixed_val&0x00FFFFFF) * 0.001)
	return float_val
}

func float_to_fixed824(float_val Crono_float_t) (fixed_val uint32) {
	whole_part := (uint32)(float_val)
	dec_part := (uint32)((float32(float_val) - float32(whole_part)) * 1000)
	fixed_val = whole_part<<24 + dec_part
	return fixed_val
}
