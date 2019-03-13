#pragma once
#ifdef CoreDll
#define CoreAPI _declspec(dllexport)
#else
#define CoreAPI  _declspec(dllimport)
#endif

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <set>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <limits>
#include <list>
#include <stack>
#define DEBUG 0
using namespace std;

typedef struct WordNode
{
	std::string name;
	int num;
	int len;
}node;


class PreProcess
{
public:
	PreProcess();
	PreProcess(char* wordss[], int len, int r);
	PreProcess(string str, int n, char* words[], int r); //str: whole txt file, generate words and graph
	int ringNum = 0;
	int num = 0;
	vector< vector<node> > ringGraph;
	vector< vector<node> > graph;
	int wordn = 0;
	PreProcess(string str, int r);   //str:path  r:ifRing  generate vector graph
	~PreProcess();
	void printGraph();
	void printRingGraph();
	int ifExist[26][26] = {};
	void print(vector <string> ary);
	void VecToStr(char* result[], vector <string> ans);

private:
	int ring = 0;
	string path;
	//bool cmpLen(const node &str1, const node &str2);
	void GenGraph();
	void strToVector(char* words[]);
	int strToWords(string temp, char* words[]);
	vector <vector < vector <string> > > checkR;
};


class DFS
{
public:
	DFS();
	~DFS();
	DFS(PreProcess pp);
	void getGraph();
	bool hasRing(int ring);

	vector<vector<node>> graph;


private:
	//int getMaxLen();
	//void DFSroute(int len, int start, int lastLetter, int endLetter);
	//vector<string> getResult();
	//vector<string> findMax();
	//vector<string> findMax(bool SorE, char letter);
	//void setEndLetter(int num);
	//void notDFS(int start);
	vector<string> result;
	int maxLen;
	int endLetter;
	vector<int> tellRepeat;           //judge if has ring ; len == ringnum
	PreProcess PreP;
	vector<string> route;
	int inDArray[26] = { 0 };

	vector<int> topoArray;
};



class RingDFS
{
public:
	RingDFS();
	~RingDFS();
	RingDFS(PreProcess pp);
	int ifExist[26][26] = {};

	vector <string> initDFS(int mode, int head, int tail, int ring);
	int letterLen = 0;    //total letter num of current route

private:
	vector <string> maxAns;
	vector <string>tempAns;
	int outDegree[26] = {};
	void UpdateOutDegree();
	void printCurGraph();
	void ringDFS(int beginI, int beginJ, int tempLen, int mode, int tail);
	void optDFS(int beginI, int beginJ, int mode, int tail);
	vector <int> ifCheck;
	PreProcess preP;
	vector< vector<node> > curGraph;
	int fff = 0;
	int ifFindTail = 0;
	int maxRoute[26] = {};
	int headLetter[26] = {};
	int selfRing[26] = {};
};

void Error(std::string str);
extern "C" CoreAPI int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
extern "C" CoreAPI int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);

class Core
{
public:
	Core();
	~Core();
	
	
};