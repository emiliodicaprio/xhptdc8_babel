package xhptdc8_wrapper

import "unsafe"

/*
Converts NULL-terminated string stored in byte_array to dest_string.
Maximum size is 1024.
*/
func convert_byte_array_to_string(byte_array []byte, dest_string *string) {
	const MAX_SIZE = 1024
	index_of_zero := 0
	for ; index_of_zero < MAX_SIZE; index_of_zero++ {
		if byte_array[index_of_zero] == 0 {
			break
		}
	}
	*dest_string = string(byte_array[:index_of_zero])
}

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

func float_to_fixed824(float_val Crono_float_t) (fixed_val Crono_int_t) {
	fixed_val = (Crono_int_t)(float_val * (1 << 24))
	return fixed_val
}
