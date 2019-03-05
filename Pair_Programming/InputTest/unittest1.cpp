#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include "../Pair_Programming/Input.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace InputTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			string str = "-w -h s -t a -r input.txt";
			string p = "input.txt";
			Input input = Input(str);
			Assert::AreEqual(1 , input.getMode());
			Assert::AreEqual(115, input.getHead());
			Assert::AreEqual(97, input.getTail());
			Assert::AreEqual(1, input.getIfRing());
			Assert::AreEqual(p, input.getPath());

			/*int num = 8;
			char * a[6] = ["word.exe", "-w", "-h", "s", "-t", "a", "-r", "intpu.txt"];
			string str = "-w -h s -t a -r input.txt";
			Input input = Input(str);
			Assert::AreEqual(1, input.getMode());
			Assert::AreEqual(115, input.getHead());
			Assert::AreEqual(97, input.getTail());
			Assert::AreEqual(1, input.getIfRing());
			Assert::AreEqual(p, input.getPath());*/
		}

	};
}