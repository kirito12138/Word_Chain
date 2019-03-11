#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Pair_Programming/Input.h"
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace InputTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			Input input("-w -h a -t z input.txt");
			Assert::AreEqual(1 ,input.getMode());
			Assert::AreEqual(int('a'), input.getHead());
			Assert::AreEqual(int('z'), input.getTail());
			Assert::AreEqual(0, input.getIfRing());
			string str("input.txt");
			Assert::AreEqual(str, input.getPath());
		}

	};
}