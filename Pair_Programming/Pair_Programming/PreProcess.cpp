#include "pch.h"
#include "PreProcess.h"
#include <string>
#include "ConstValues.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Error.h"
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;
PreProcess::PreProcess()
{

}
PreProcess::PreProcess(string str)
{
	this->path = str;
	ringGraph.resize(26);
	graph.resize(26);
	GenGraph();
	/*for (int i = 0; i < ringNum; i++)
	{
		ifCheck.push_back(0);
	}*/
	
}
PreProcess::PreProcess(string str, int f, char* words[])
{
	int n;
	ringGraph.resize(26);
	graph.resize(26);
	n = strToWords(str, words);
	/*for (int i = 0; i < n; i++)
	{
		cout << words[i] << endl;
	}*/
	//strToVector();
	//printGraph();

}
PreProcess::PreProcess(char* wordss[], int len)
{
	ringGraph.clear();
	graph.clear();
	ringGraph.resize(26);
	//cout << "22222222222222" << endl;
	graph.resize(26);
	wordn = len;
	strToVector(wordss);
	//printGraph();
	
	//cout << "2" << endl;
}


PreProcess::~PreProcess()
{
}

bool cmpLen(const node &str1, const node &str2)
{
	return str1.len > str2.len;
}

void PreProcess::GenGraph()
{
	string temp;
	ifstream file(this->path, ios::_Nocreate);
	int tempn, graphn;
	int i, j;
	int wordBegin = 0;
	int h, t;
	if (!file)
	{
		Error("Input File Doesn't Exit");
	}
	while (file >> temp)
	{
		tempn = temp.size();
		for (i = 0; i < tempn; i++) {
			if (!isalpha(temp[i]))
			{
				continue;
			}
			wordBegin = i;
			while (isalpha(temp[i]) && i<tempn)
			{
				temp[i] = tolower(temp[i]);
				i++;
			}
			node newN = { temp.substr(wordBegin, i - wordBegin), (PreProcess::ringNum)++, i - wordBegin };
			h = newN.name[0] - 'a';
			t = newN.name[i - wordBegin - 1] - 'a';
			ringGraph[h].push_back(newN);
			if ((i - wordBegin) > ifExist[h][t] && ifExist[h][t]!=0)
			{
				if (h == t)
				{
					Error("Multiple Self Ring Found");
				}
				ifExist[h][t] = i - wordBegin;
				graphn = graph[h].size();
				for (j = 0; j < graphn; j++) 
				{
					if (graph[h][j].name[graph[h][j].name.size() - 1] == t + 'a')
					{
						graph[h][j] = newN;
						break;
					}
				}
			}
			else if (ifExist[h][t] == 0)
			{
				ifExist[h][t] = i - wordBegin;
				graph[h].push_back(newN);
				PreProcess::num++;
			}
			else
			{
				continue;
			}
		}
	}
	file.close();
	if (PreProcess::num <= 1)
	{
		Error("No Word Chain in File");
	}
	for (i = 0; i < 26; i++)
	{
		sort(ringGraph[i].begin(), ringGraph[i].end(), &cmpLen);
	}
}

void PreProcess::printGraph() {
	int i = 0, j=0;
	char c;
	int len;
	for (i; i < 26; i++)
	{
		c = i + 'a';
		cout << c << " Words -----------------------" << endl;
		len = graph[i].size();
		for (j = 0; j < len; j++)
		{
			cout << graph[i][j].name << endl;
		}
		cout << "================================\n\n" << endl;
	}
}

void PreProcess::printRingGraph() {
	int i = 0, j = 0;
	char c;
	int len;
	for (i; i < 26; i++)
	{
		c = i + 'a';
		cout << c << " Words -----------------------" << endl;
		len = ringGraph[i].size();
		for (j = 0; j < len; j++)
		{
			cout << ringGraph[i][j].name << endl;
		}
		cout << "================================\n\n" << endl;
	}
}

void PreProcess::print(vector <string> ary)
{
	ofstream slt("solution.txt");
	int i;
	for (i = 0; i < ary.size(); i++)
	{
		slt << ary[i] << endl;
	}
	slt.close();
}

void PreProcess::strToVector(char* words[])
{
	int i = 0, j;
	int graphn;
	int h, t;
	int len = wordn;
	for (i = 0; i < len; i++)
	{
		//cout << words[i] << endl;
		string ss = words[i];
		node newN = { ss, (PreProcess::ringNum)++, ss.size() };
		h = newN.name[0] - 'a';
		t = newN.name[ss.size() - 1] - 'a';
		ringGraph[h].push_back(newN);
		if ((strlen(words[i])) > ifExist[h][t] && ifExist[h][t] != 0)
		{
			if (h == t)
			{
				Error("Multiple Self Ring Found");
			}
			ifExist[h][t] = strlen(words[i]);
			graphn = graph[h].size();
			for (j = 0; j < graphn; j++)
			{
				if (graph[h][j].name[graph[h][j].name.size() - 1] == t + 'a')
				{
					graph[h][j] = newN;
					break;
				}
			}
		}
		else if (ifExist[h][t] == 0)
		{
			ifExist[h][t] = strlen(words[i]);
			graph[h].push_back(newN);
			PreProcess::num++;
		}
		else
		{
			continue;
		}
	}
	for (i = 0; i < len; i++)
	{
		free(words[i]);
	}
	if (PreProcess::num <= 1)
	{
		Error("No Word Chain in File");
	}
	for (i = 0; i < 26; i++)
	{
		sort(ringGraph[i].begin(), ringGraph[i].end(), &cmpLen);
	}
}

void PreProcess::VecToStr(char* result[], vector <string> ans)
{
	int i = 0, j=0;
	for (i = 0; i < ans.size(); i++)
	{
		const int len = ans[i].length();
		result[i] = new char[len + 1];
		//strcpy_s(result[i], len+1,ans[i].c_str());
		for (j = 0; j < len; j++)
		{
			result[i][j] = ans[i][j];
		}
		result[i][len] = '\0';
	}
	return;
}


int PreProcess::strToWords(string temp, char* words[])
{
	int i = 0, j = 0;
	int graphn;
	int h, t;
	int tempn = temp.size();
	int count = 0;
	int wordBegin;
	char singleWord[500];
	
	for (i = 0; i < tempn; i++) {
		//string word = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		if (!isalpha(temp[i]))
		{
			continue;
		}
		wordBegin = i;
		while (isalpha(temp[i]) && i < tempn)
		{
			temp[i] = tolower(temp[i]);
			i++;
		}
		//word = temp.substr(wordBegin, i - wordBegin);
		//const int ll = word.length();
		
		const int ll = i - wordBegin;
		
		//strcpy_s(words[count], ll+1, word.c_str());
		for (j = 0; j < ll; j++)
		{
			singleWord[j] = temp[wordBegin + j];
		}
		//words[count][ll] = '\0';
		singleWord[ll] = '\0';
		//words[count] = new char(ll+1);
		words[count] = (char *)malloc(sizeof(char) * (ll + 1));
		strcpy_s(words[count], ll + 1, singleWord);
		count++;
		/*h = temp[wordBegin] - 'a';
		t = temp[i - 1] - 'a';
		if (ifExist[h][t] != 0)
		{
			if (h == t)
			{
				Error("Multiple Self Ring Found");
			}
			ifExist[h][t] = i - wordBegin;
		}
		ifExist[h][t] = ifExist[h][t] > (i - wordBegin) ? ifExist[h][t] : (i - wordBegin);*/
		
	}
	
	if (count <= 1)
	{
		Error("No Word Chain in File");
	}
	wordn = count;
	return count;
}
int PreProcess::num = 0;
int PreProcess::ringNum = 0;