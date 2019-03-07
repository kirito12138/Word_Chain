#include "pch.h"
#include "DFS.h"
#include <string>
#include "Error.h"
#include "PreProcess.h"
#include "ConstValues.h"
#include <vector>


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
void DFS::getGraph(PreProcess &p) {
	this->graph = p.graph;
}
void DFS::DFSroute(vector<string> route, int len, int start, int lastLetter)
{
	unsigned int i;

	for (i = 0; i < graph[start].size(); i++) {
		int tmp = graph[start][i].name[0] - 'a';//if all.tolow()!!
		if (lastLetter == tmp) {
			continue;
		}
		route.push_back(graph[start][i].name);
		len += graph[start][i].len;
		this->DFSroute(route, len, tmp, start);
	}
	if (len > this->maxLen) {
		this->maxLen = len;
		result = route;
		result.push_back(graph[start][i].name);
	}
}
/*bool DFS::hasRing()
{
	int i;
	int inDArray[26];
	queue<int> zeroDArray;//transfer graph to in-degree array
	vector<int> topoArray;
	int topo_i = 0;//index of topoArray

	for (i = 0; i < 26; i++) {
		inDArray[i] = graph[i].size();
		if (graph[i].size() == 0) {
			zeroDArray.push(i);
		}
	}

	while (!zeroDArray.empty()) {
		int topE = zeroDArray.front();
		zeroDArray.pop();
		topoArray.push_back(topE);

		for (unsigned int i = 0; i < graph[topE].size(); i++) {
			int tmp = graph[topE][i].name[0] - 'a';//if all.tolow()!!
			inDArray[i]--;
			if (inDArray[i] == 0) {
				zeroDArray.push(i);
			}
		}
	}

	if (topoArray.size() == 26) {
		return true;
	}
	return false;
}*/
int DFS::getMaxLen() {
	return maxLen;
}
vector<string> DFS::getResult() {
	return result;
}