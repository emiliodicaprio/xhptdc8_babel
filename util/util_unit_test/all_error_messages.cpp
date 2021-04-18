#include "pch.h"
#include "CppUnitTest.h"
#include "xhptdc8_util.h"
#include "xhptdc8_interface.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace get_all_error_messages	
{
#define hMgr_INIT_BLOCK \
	xhptdc8_manager hMgr;	\
	xhptdc8_manager_init_parameters params;	\
	int error_code;	\
	char* error_message = NULL;	\
	xhptdc8_get_default_init_parameters(&params); \
	hMgr = xhptdc8_init(&params, &error_code, (const char**)&error_message);	\

#define hMgr_CLEANUP_BLOCK \
		xhptdc8_close(hMgr);

	TEST_CLASS(happy_scenario)
	{
	public:
		TEST_METHOD(include_ok_true_fixed_length_true)
		{
			hMgr_INIT_BLOCK;
			std::string err_messages_str = xhptdc8_get_all_error_messages(hMgr, true, true);
			hMgr_CLEANUP_BLOCK;
			Assert::AreNotEqual(std::string::npos, err_messages_str.find("0, \"OK\""));
			Assert::AreNotEqual(std::string::npos, err_messages_str.find("1, \"Board does not exist.\""));
			Assert::AreNotEqual(std::string::npos, err_messages_str.find("2, \"Board does not exist.\""));
			Assert::AreNotEqual(std::string::npos, err_messages_str.find("3, \"Board does not exist.\""));
			Assert::AreNotEqual(std::string::npos, err_messages_str.find("4, \"Board does not exist.\""));
			Assert::AreNotEqual(std::string::npos, err_messages_str.find("5, \"Board does not exist.\""));
			Assert::AreNotEqual(std::string::npos, err_messages_str.find("6, \"Board does not exist.\""));
			Assert::AreNotEqual(std::string::npos, err_messages_str.find("7, \"Board does not exist.\""));
		}
		TEST_METHOD(include_ok_true_fixed_length_false)
		{
			hMgr_INIT_BLOCK;
			std::string err_messages_str = xhptdc8_get_all_error_messages(hMgr, true, false);
			hMgr_CLEANUP_BLOCK;
			Assert::AreNotEqual(std::string::npos, err_messages_str.find("0, \"OK\""));
			Assert::AreEqual(std::string::npos, err_messages_str.find("1, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("2, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("3, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("4, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("5, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("6, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("7, "));
		}
		TEST_METHOD(include_ok_false_fixed_length_true)
		{
			hMgr_INIT_BLOCK;
			std::string err_messages_str = xhptdc8_get_all_error_messages(hMgr, true, false);
			hMgr_CLEANUP_BLOCK;
			Assert::AreNotEqual(std::string::npos, err_messages_str.find("0, \"OK\""));
			Assert::AreEqual(std::string::npos, err_messages_str.find("1, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("2, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("3, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("4, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("5, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("6, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("7, "));
		}
		TEST_METHOD(include_ok_false_fixed_length_false)
		{
			hMgr_INIT_BLOCK;
			std::string err_messages_str = xhptdc8_get_all_error_messages(hMgr, false, false);
			hMgr_CLEANUP_BLOCK;
			Assert::AreEqual(std::string::npos, err_messages_str.find("0, OK"));
			Assert::AreEqual(std::string::npos, err_messages_str.find("1, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("2, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("3, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("4, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("5, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("6, "));
			Assert::AreEqual(std::string::npos, err_messages_str.find("7, "));
			Assert::AreEqual(err_messages_str.length(), (size_t)0);
		}
	};
	TEST_CLASS(special_cases)
	{
	public:
		TEST_METHOD(wrong_argument_param)
		{
			xhptdc8_manager hMgr;	
			int error_code;	
			char* error_message = NULL;	
			hMgr = xhptdc8_init(NULL, &error_code, (const char**)&error_message);
			std::string err_messages_str = xhptdc8_get_all_error_messages(hMgr, true, true);
			hMgr_CLEANUP_BLOCK;

			Assert::AreEqual(std::string::npos, err_messages_str.find("-1, \"Invalid arguments.\""));
		}
		TEST_METHOD(wrong_argument_hMgr)
		{
			std::string err_messages_str = xhptdc8_get_all_error_messages(NULL, true, true);

			Assert::AreEqual(std::string::npos, err_messages_str.find("-1, \"Invalid arguments.\""));
		}
		TEST_METHOD(error_count_devices)
		{
			/*
			Need to know how to reporduce
			Assert::AreEqual(std::string::npos, err_messages_str.find("-2, \"count_devices() returned error <17> (null) in get_all_error_messages().\""));
			*/
		}
	};
};
