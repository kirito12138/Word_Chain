#include "pch.h"
#include "Core.h"
#include <iostream>
#include "Input.h"
#include "PreProcess.h"
#include "DFS.h"
#include <string>
#include <vector>
#include "RingDFS.h"
#include "Core.h"
using namespace std;

Core::Core()
{
}


Core::~Core()
{
}


int Core::gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
	PreProcess ppa(words, len);
	//cout << "1" << endl;
	RingDFS rd(ppa);
	DFS dfs(ppa);
	//ppa.printGraph();
	dfs.getGraph();
	dfs.hasRing();

	vector <string> ans = rd.initDFS(1, head, tail, enable_loop);
	ppa.VecToStr(result, ans);
	ppa.print(ans);
	return 1;
}
int Core::gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
	PreProcess ppa(words, len);
	RingDFS rd(ppa);
	DFS dfs(ppa);
	dfs.getGraph();
	dfs.hasRing();
	vector <string> ans = rd.initDFS(2, head, tail, enable_loop);
	ppa.VecToStr(result, ans);
	ppa.print(ans);
	return 1;
}
