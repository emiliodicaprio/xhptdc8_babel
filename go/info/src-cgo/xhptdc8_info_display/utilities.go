package xhptdc8_info_display

import "unsafe"

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
	float_val = ((Crono_float_t)(fixed_val) / (1 << 24))
	return float_val
}
