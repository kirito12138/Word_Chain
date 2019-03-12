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

using namespace std;


int main(int argc, char * argv[])
{
    //std::cout << "Hello World!\n"; 
	//Input input = Input(argc, argv);
	//cout << input.getInput() << endl;
	//PreProcess pp("input.txt");
	//pp.printGraph();
	//pp.printRingGraph();
	//cout << PreProcess::ringNum << "   " << PreProcess::num << endl;

	/*int i, j, k;
	Input input = Input(argc, argv);
	PreProcess pp(input.getPath());
	DFS dfs(pp);
	vector < vector<string> > ans;
	for (i=0;i<26)*/
	

	/*vector<string>r;
	//r = dfs.findMax();
	dfs.getGraph();
	dfs.hasRing();
	for (int i = 0; i < 26; i++) {
		dfs.notDFS(i);
	}
	for (int i = 0; i < dfs.getResult().size(); i++) {
		cout << dfs.getResult()[i] << endl;
	}
	//int i = 0;
	//while (i < r.size()) {
	//	cout << r[i++] << endl;
	//}

	system("pause");*/


	//====================================================
	/*Input input = Input("-w input.txt");
	PreProcess pp(input.getPath());
	DFS dfs = DFS(pp);
	RingDFS rd(pp);
	dfs.getGraph();
	dfs.hasRing();
	vector <string> ans = rd.initDFS(input.getMode(), input.getHead(), input.getTail(), input.getIfRing());
	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << endl;
	}
	pp.print(ans);*/
	try
	{
		char*words[10000];
		/*for (int i = 0; i < 10000; i++) {
			words[i] = new char(100);
		}*/
		Input input = Input("-w -r input.txt");
		PreProcess pp(input.longStr, 1, words, input.getIfRing());
		DFS dfs(pp);
		dfs.getGraph();
		dfs.hasRing(input.getIfRing());
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
