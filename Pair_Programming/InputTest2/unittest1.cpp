#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace InputTest2
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			Input input = Input("-w -h a -t z ..\\Pair_Programming\\hard.txt");

			//Input input("-w -h a -t z input.txt");
			Assert::AreEqual(1, input.getMode());
			Assert::AreEqual(int('a'), input.getHead());
			Assert::AreEqual(int('z'), input.getTail());
			Assert::AreEqual(0, input.getIfRing());
		}

	};
}