#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PrePandRingDFSTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char* words[10000];
			// TODO: 在此输入测试代码
			PreProcess pp1("..\\Pair_Programming\\PrePTest.txt", 0);
			Assert::AreEqual(pp1.ringNum, 8);
			Assert::AreEqual(pp1.num, 7);
			PreProcess pp2("ab bc cd de ee", 1, words, 0);
			Assert::AreEqual(pp2.wordn, 5);
			PreProcess pp3(words, 5, 0);
			Assert::AreEqual(pp3.ringNum, 5);
			pp3.printGraph();
			pp3.printRingGraph();
			vector <string> vct;
			vct.push_back("111");
			vct.push_back("222");
			vct.push_back("333");
			pp3.print(vct);

		}
		TEST_METHOD(TestMethod2)
		{
			Input input = Input("-w ..\\Pair_Programming\\PrePTest.txt");
			PreProcess pp(input.getPath(), 0);
			DFS dfs = DFS(pp);
			RingDFS rd(pp);
			dfs.getGraph();
			dfs.hasRing(0);
			vector <string> ans = rd.initDFS(input.getMode(), input.getHead(), input.getTail(), input.getIfRing());
			int l = ans.size();
			Assert::AreEqual(5, l);
		}
	};
}