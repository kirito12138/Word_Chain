#include "pch.h"
#include "PreProcess.h"
#include <string>
#include "ConstValues.h"
#include <vector>
#include <fstream>
#include "Error.h"
#include <algorithm>
#include <set>
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
	if (PreProcess::num == 0)
	{
		Error("No Words in File");
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

void PreProcess::print(string* ary, int num)
{
	ofstream slt("solution.txt");
	int i;
	for (i = 0; i < num; i++)
	{
		slt << ary[i] << endl;
	}
	slt.close();
}



int PreProcess::num = 0;
int PreProcess::ringNum = 0;