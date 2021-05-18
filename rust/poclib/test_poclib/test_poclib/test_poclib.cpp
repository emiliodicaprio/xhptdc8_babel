// test_poclib.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define XHPTDC8_API_IMP __declspec(dllimport)

typedef struct {
	int64_t time;
	uint16_t bin;
	uint8_t channel;
	uint8_t type;
} TDCHit;

extern "C" {
	XHPTDC8_API_IMP void set_TDCHit(TDCHit* hit);
	XHPTDC8_API_IMP void get_TDCHit(TDCHit* hit);
	XHPTDC8_API_IMP void set_Str(char* str);
	XHPTDC8_API_IMP void get_Str(char* str, unsigned char size);
}

int main()
{
	fprintf(stdout, "--------------------------------------------------------------\n");
	fprintf(stdout, "Test #1 - Pass struct to RUST DLL API ------------------------\n");
	fprintf(stdout, "--------------------------------------------------------------\n");
	TDCHit hit{ 123456789, 257, 255, 1};
	fprintf(stdout, "POC Test Application: Calling Rust DLL API 'set_TDCHit' with struct info: \n"
		"- time: %llu\n- bin: %u\n- channel: %u\n- type: %u\n",
		hit.time, hit.bin, hit.channel, hit.type);
	fprintf(stdout, "\n");
	set_TDCHit(&hit);

	fprintf(stdout, "\n");
	fprintf(stdout, "--------------------------------------------------------------\n");
	fprintf(stdout, "Test #2 - Filling struct from RUST DLL API -------------------\n");
	fprintf(stdout, "--------------------------------------------------------------\n");
	TDCHit hitRet;
	get_TDCHit(&hitRet);
	fprintf(stdout, "\n");
	fprintf(stdout, "POC Test Application: Calling Rust DLL API 'get_TDCHit' filling struct info: \n"
		"- time: %llu\n- bin: %u\n- channel: %u\n- type: %u\n",
		hitRet.time, hitRet.bin, hitRet.channel, hitRet.type);

	fprintf(stdout, "\n");
	fprintf(stdout, "--------------------------------------------------------------\n");
	fprintf(stdout, "Test #3 - Pass string to RUST DLL API ------------------------\n");
	fprintf(stdout, "--------------------------------------------------------------\n");
	char test_str[64] = {"This is a test string from C Application!"};
	fprintf(stdout, "POC Test Application: Calling Rust DLL API 'set_Str' with string info: \n"
		"- String: %s\n", test_str);
	fprintf(stdout, "\n");
	set_Str(test_str);

	fprintf(stdout, "\n");
	fprintf(stdout, "--------------------------------------------------------------\n");
	fprintf(stdout, "Test #4 - Filling string from RUST DLL API -------------------\n");
	fprintf(stdout, "--------------------------------------------------------------\n");
	char buff[100];
	get_Str(buff, 100);
	fprintf(stdout, "\n");
	fprintf(stdout, "POC Test Application: Calling Rust DLL API 'get_Str' filling string info: \n"
		"- String: %s\n", buff);
}
