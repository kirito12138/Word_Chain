#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DFSTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: 在此输入测试代码
			PreProcess pp1("..\\Pair_Programming\\DFSTest1.txt", 1);
			PreProcess pp2("..\\Pair_Programming\\DFSTest2.txt", 0);
			DFS dfs1(pp1);
			DFS dfs2(pp2);
			dfs1.getGraph();
			dfs2.getGraph();
			Assert::AreEqual(true, dfs1.hasRing());
			Assert::AreEqual(false, dfs2.hasRing());
		}

	};
}