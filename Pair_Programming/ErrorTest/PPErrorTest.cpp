#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ErrorTest
{
	TEST_CLASS(UnitTest1)// Input Error Test
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			try
			{
				PreProcess pp ("noFile.txt", 0);
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Input File Doesn't Exit";
				Assert::AreEqual(s, str);
			}

			try
			{
				PreProcess pp("..\\Pair_Programming\\PPErrorTest1.txt", 0);
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Multiple Self Ring Found";
				Assert::AreEqual(s, str);
			}

			try
			{
				PreProcess pp("..\\Pair_Programming\\PPErrorTest2.txt", 0);
			}
			catch (string str)
			{
				string s = "No Word Chain in File";
				Assert::AreEqual(s, str);
			}

			try
			{
				PreProcess pp("..\\Pair_Programming\\DFSTest1.txt", 0);
				DFS dfs(pp);
				dfs.getGraph();
				dfs.hasRing(0);
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Ring Detected When not Allowed";
				Assert::AreEqual(s, str);
			}

		}

	};
}