package xhptdc8_wrapper

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
