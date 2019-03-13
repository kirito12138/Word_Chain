// Pair_Programming.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "Input.h"
#include "PreProcess.h"
#include "DFS.h"
#include <string>
#include <vector>
#include "RingDFS.h"
#include "Core.h"
#include <cstring>
#include <string.h>
#include <Windows.h>

#define IFDLL 0
using namespace std;

typedef int(*ptr_word)(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
typedef int(*ptr_char)(char* words[], int len, char* result[], char head, char tail, bool enable_loop);


char*words[10000];
int main(int argc, char * argv[])
{

	try
	{
		if (IFDLL == 0)
		{
			Input input = Input(argc, argv);
			PreProcess pp(input.longStr, 1, words, input.getIfRing());
			Core core = Core();
			char* result[60];
			if (input.getMode() == 1)
			{
				core.gen_chain_word(words, pp.wordn, result, input.getHead(), input.getTail(), input.getIfRing());
			}
			else
			{
				core.gen_chain_char(words, pp.wordn, result, input.getHead(), input.getTail(), input.getIfRing());
			}
		}
		//Input input = Input("-w hard.txt");
		else
		{
			HINSTANCE CoreDLL = LoadLibrary("Core.dll");
			ptr_word gen_chain_word = (ptr_word)GetProcAddress(CoreDLL, "gen_chain_word");
			ptr_char gen_chain_char = (ptr_word)GetProcAddress(CoreDLL, "gen_chain_char");
			//Input input = Input("-w hard.txt");
			Input input = Input(argc, argv);
			PreProcess pp(input.longStr, 1, words, input.getIfRing());
			char* result[60];
			if (input.getMode() == 1)
			{
				gen_chain_word(words, pp.wordn, result, input.getHead(), input.getTail(), input.getIfRing());
			}
			else
			{
				gen_chain_char(words, pp.wordn, result, input.getHead(), input.getTail(), input.getIfRing());
			}
		}
	}
	catch (string str)
	{
		cout << str << endl;
	}

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
