#include "pch.h"
#include "DFS.h"
#include <string>
#include "Error.h"
#include "PreProcess.h"
#include "ConstValues.h"
#include <vector>
#include <queue>

using namespace std;


DFS::DFS()
{
}


DFS::~DFS()
{
}

DFS::DFS(PreProcess pp) {
	result.resize(50);
	maxLen = 0;
	tellRepeat.resize(PreProcess::ringNum);
	PreP = pp;
}
void DFS::getGraph() {
	this->graph = PreP.graph;
}
void DFS::DFSroute(int len, int start, int lastLetter)
{
	unsigned int i;

	for (i = 0; i < graph[start].size(); i++) {
		int tmp = graph[start][i].len;    //if all.tolow()!!
		tmp = graph[start][i].name[tmp -1] - 'a';
		if (lastLetter == tmp) {
			continue;
		}
		len += graph[start][i].len;
		route.push_back(graph[start][i].name);

		this->DFSroute(len, tmp, start);

		route.pop_back();
		len -= graph[start][i].len;
	}
	if (len > this->maxLen) {
		this->maxLen = len;
		result = route;
	}
	
}
bool DFS::hasRing()
{
	int i;
	int inDArray[26] = { 0 };
	queue<int> zeroDArray;//transfer graph to in-degree array
	vector<int> topoArray;
	int topo_i = 0;//index of topoArray

	for (i = 0; i < 26; i++) {
		for (unsigned int j = 0; j < graph[i].size(); j++) {
			int tmp = graph[i][j].len;     //if all.tolow()!!
			tmp = graph[i][j].name[tmp - 1] - 'a';
			if (tmp != i) {
				inDArray[tmp]++;
			}
		}
	}
	for (i = 0; i < 26; i++) {
		if (inDArray[i] == 0) {
			zeroDArray.push(i);
		}
	}
	while (!zeroDArray.empty()) {
		int topE = zeroDArray.front();
		topoArray.push_back(topE);
		zeroDArray.pop();

		for (unsigned int i = 0; i < graph[topE].size(); i++) {
			int tmp = graph[topE][i].len;     //if all.tolow()!!
			tmp = graph[topE][i].name[tmp - 1] - 'a';
			if (tmp != topE) {
				inDArray[tmp]--;
				if (inDArray[tmp] == 0) {
					zeroDArray.push(tmp);
				}
			}
		}
	}

	if (topoArray.size() == 26) {
		return false;
	}
	return true;
}
int DFS::getMaxLen() {
	return maxLen;
}
vector<string> DFS::getResult() {
	return result;
}
void DFS::setEndLetter(int num) {
	this->endLetter = num;
}