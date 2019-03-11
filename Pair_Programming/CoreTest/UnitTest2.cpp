#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreTest
{
	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(TestMethod2)
		{
			// TODO: ‘⁄¥À ‰»Î≤‚ ‘
			int ansLen;
			try
			{
				char*words[10000];
				/*for (int i = 0; i < 10000; i++) {
					words[i] = new char(100);
				}*/
				Input input = Input("-c -t f ..\\Pair_Programming\\hard.txt");
				PreProcess pp(input.longStr, 1, words, input.getIfRing());
				Core core = Core();
				char* result[60];
				ansLen = core.gen_chain_char(words, pp.wordn, result, input.getHead(), input.getTail(), input.getIfRing());

			}
			catch (string str)
			{
				cout << str << endl;
			}
			Assert::AreEqual(20, ansLen);
		}

	};
}