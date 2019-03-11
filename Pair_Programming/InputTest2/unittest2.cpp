#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace InputTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(TestMethod2)
		{
			// TODO: 在此输入测试代码
			char* p[7];
			string s;
			s = "-w";
			p[0] = new char[2];
			p[1] = new char[3];
			p[2] = new char[3];
			p[3] = new char[2];
			p[4] = new char[3];
			p[5] = new char[2];
			p[6] = new char[100];
			p[0][0] = 'a';
			p[0][1] = '\0';
			strcpy_s(p[1], s.size() + 1, s.c_str());
			p[1][s.size()] = '\0';
			s = "-h";
			strcpy_s(p[2], s.size() + 1, s.c_str());
			p[2][s.size()] = '\0';
			p[3][0] = 'a';
			p[3][1] = '\0';
			s = "-t";
			strcpy_s(p[4], s.size() + 1, s.c_str());
			p[4][s.size()] = '\0';
			p[5][0] = 'z';
			p[5][1] = '\0';
			s = "..\\Pair_Programming\\hard.txt";
			strcpy_s(p[6], s.size() + 1, s.c_str());
			p[6][s.size()] = '\0';
			Input input = Input(7, p);

			//Input input("-w -h a -t z input.txt");
			Assert::AreEqual(1, input.getMode());
			Assert::AreEqual(int('a'), input.getHead());
			Assert::AreEqual(int('z'), input.getTail());
			Assert::AreEqual(0, input.getIfRing());
		}

	};
}