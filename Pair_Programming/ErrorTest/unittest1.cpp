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
				Input input("-w -c ..\\Pair_Programming\\DFSTest2.txt");
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Chain Type Parameter Error";
				Assert::AreEqual(s, str);
			}

			try
			{
				Input input("-w -h a -h a ..\\Pair_Programming\\DFSTest2.txt");
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Head Duplicate Definition Error";
				Assert::AreEqual(s, str);
			}

			try
			{
				Input input("-w -ha ..\\Pair_Programming\\DFSTest2.txt");
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Lack Space Error";
				Assert::AreEqual(s, str);
			}

			try
			{
				Input input("-w -h + ..\\Pair_Programming\\DFSTest2.txt");
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Head Letter Error";
				Assert::AreEqual(s, str);
			}

			try
			{
				Input input("-w -t a -t a ..\\Pair_Programming\\DFSTest2.txt");
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Tail Duplicate Definition Error";
				Assert::AreEqual(s, str);
			}

			try
			{
				Input input("-w -ta ..\\Pair_Programming\\DFSTest2.txt");
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Lack Space Error";
				Assert::AreEqual(s, str);
			}

			try
			{
				Input input("-w -t + ..\\Pair_Programming\\DFSTest2.txt");
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Tail Letter Error";
				Assert::AreEqual(s, str);
			}

			try
			{
				Input input("-w -r -r ..\\Pair_Programming\\DFSTest2.txt");
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Ring Parameter Duplicate";
				Assert::AreEqual(s, str);
			}

			try
			{
				Input input("-w -z ..\\Pair_Programming\\DFSTest2.txt");
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Parameter Type Error";
				Assert::AreEqual(s, str);
			}

			try
			{
				Input input("-h a ..\\Pair_Programming\\DFSTest2.txt");
				Assert::AreEqual("Error Test Didn't Throw Error!", " ");
			}
			catch (string str)
			{
				string s = "Lack Chain Type Parameter";
				Assert::AreEqual(s, str);
			}
		}

	};
}