#include "stdafx.h"
#include "CppUnitTest.h"
#include <Windows.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
typedef int(*ptr_word)(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
typedef int(*ptr_char)(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
namespace CoreTest
{
	HINSTANCE CoreDLL = LoadLibrary("Core.dll");

	TEST_CLASS(UnitTest4)
	{
	public:

		TEST_METHOD(TestMethod4)
		{
			// TODO: ‘⁄¥À ‰»Î≤‚ ‘
			int ansLen;
			try
			{
				if (CoreDLL == NULL) {
					Error("File 'Core.dll' not found.");
					
				}

				ptr_word gen_chain_word = (ptr_word)GetProcAddress(CoreDLL, "gen_chain_word");
				ptr_char gen_chain_char = (ptr_word)GetProcAddress(CoreDLL, "gen_chain_char");
				if (gen_chain_word == NULL || gen_chain_char == NULL) {
					Error("Invalid file 'Core.dll'.");

				}

				char*words[10000];
				/*for (int i = 0; i < 10000; i++) {
					words[i] = new char(100);
				}*/
				Input input = Input("-w -h d ..\\Pair_Programming\\hard.txt");
				PreProcess pp(input.longStr, 1, words, input.getIfRing());
				Core core = Core();
				char* result[60];

				ansLen = gen_chain_word(words, pp.wordn, result, input.getHead(), input.getTail(), input.getIfRing());

			}
			catch (string str)
			{
				string s = "No Exception Allowed";
				Assert::AreEqual(str, s);
			}
			Assert::AreEqual(27, ansLen);
		}

	};
}