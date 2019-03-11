#include "pch.h"
#include "DFS.h"
#include <string>
#include "Error.h"
#include "PreProcess.h"
#include "ConstValues.h"
#include <vector>
#include <queue>
#include <limits>
#include <list>
#include <stack>
using namespace std;


DFS::DFS()
{
}


DFS::~DFS()
{
}

DFS::DFS(PreProcess pp) {
	maxLen = 0;
	tellRepeat.resize(PreProcess::ringNum);
	PreP = pp;
}
void DFS::getGraph() {
	this->graph = PreP.graph;
}

vector<string> DFS::findMax() {
	this->getGraph();
	bool r = this->hasRing();
	if (r) {
		Error("route has ring!\n");
	}
	else {
		for (int i = 0; i < 26; i++) {
			if (inDArray[i] == 0) {
				this->DFSroute(0, i, -1 , -1);
			}
		}
	}
	return this->getResult();
}


vector<string> DFS::findMax(bool SorE , char letter) {
	this->getGraph();
	bool r = this->hasRing();
	if (r) {
		Error("route has ring!\n");
	}
	else {
		if (SorE) {
			this->DFSroute(0, letter - 'a', -1 , -1);
		}
		else {
			for (int i = 0; i < 26; i++) {
				if (inDArray[i] == 0) {
					this->DFSroute(0, i, -1, letter-'a');
				}
			}
		}
	}
	return this->getResult();
}

/*
initial:
end = 26 or x - 'a'
*/
void DFS::notDFS(int start) {
	int route1[26];//±£¥Ê¡À graph[i][route[i]]
	int route2[26];
	int len = -1;
	int tmp = -1;
	for (int i = 0; i < 26; i++) {
		route2[i] = -1;
	}
	int dist[26];
	int topo_i = 0;
	for (int i = 0; i < 26; i++) {
		dist[i] = INT_MIN;
	}
	dist[start] = 0;

	while (topo_i != 26) {
		int u = topoArray[topo_i++];
		if (dist[u] != INT_MIN) {
			for (int i = 0; i < graph[u].size(); i++) {
				tmp = graph[u][i].len;    //if all.tolow()!!
				tmp = graph[u][i].name[tmp - 1] - 'a';
				if (dist[tmp] < dist[u] + graph[u][i].len) {
					//route1[u] = i;
					//route2[u] = tmp;
					dist[tmp] = dist[u] + graph[u][i].len;
					if (dist[tmp] > len) {
						len = dist[tmp];
					}
				}
			}
		}
	}
	if (len > maxLen) {
		maxLen = len;
		//result.clear();
		//for (int i = start; route2[i] != -1; i = route2[i]) {
		//	result.push_back( graph[i][route1[i]].name );
		//}
	}
	
}

void DFS::DFSroute(int len, int start, int lastLetter ,int endLetter)
{
	unsigned int i;

	for (i = 0; i < graph[start].size(); i++) {
		int tmp = graph[start][i].len;    //if all.tolow()!!
		tmp = graph[start][i].name[tmp - 1] - 'a';
		if (endLetter == tmp) {
			route.push_back(graph[start][i].name);
			break;
		}
		if (lastLetter == tmp) {
			continue;
		}
		len += graph[start][i].len;
		route.push_back(graph[start][i].name);
		this->DFSroute(len, tmp, start, endLetter);
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
	queue<int> zeroDArray;//transfer graph to in-degree array
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