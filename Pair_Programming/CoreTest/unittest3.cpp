#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreTest
{

	TEST_CLASS(UnitTest3)
	{
	public:

		TEST_METHOD(TestMethod3)
		{
			// TODO: �ڴ��������
			int ansLen;
			try
			{
				char*words[10000];
				/*for (int i = 0; i < 10000; i++) {
					words[i] = new char(100);
				}*/
				Input input = Input("-w -h d ..\\Pair_Programming\\hard.txt");
				PreProcess pp(input.longStr, 1, words, input.getIfRing());
				Core core = Core();
				char* result[60];

				ansLen = core.gen_chain_word(words, pp.wordn, result, input.getHead(), input.getTail(), input.getIfRing());

			}
			catch (string str)
			{
				cout << str << endl;
			}
			Assert::AreEqual(27, ansLen);
		}

	};
}