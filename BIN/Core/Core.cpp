// Core.cpp : 定义 DLL 应用程序的导出函数。
//
#define CoreDll
#include "stdafx.h"
#include "Core.h"

Core::Core()
{
}


Core::~Core()
{
}




void Error(string str)
{
	throw(str);
	//cout << "Error:" << str << "!\n" << endl;
	//exit(0);
}

DFS::DFS()
{
}


DFS::~DFS()
{
}

DFS::DFS(PreProcess pp) {
	maxLen = 0;
	tellRepeat.resize(pp.ringNum);
	PreP = pp;
}
void DFS::getGraph() {
	this->graph = PreP.graph;
}

bool DFS::hasRing(int ring)
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
	if (ring == 0)
	{
		Error("Ring Detected When not Allowed");
	}
	return true;
}


RingDFS::RingDFS()
{
}


RingDFS::~RingDFS()
{
}

RingDFS::RingDFS(PreProcess pp)
{
	preP = pp;
	ifCheck.resize(preP.ringNum);
	for (int i = 0; i < 26; i++)
	{
		maxRoute[i] = -1;
	}
}

void RingDFS::ringDFS(int beginI, int beginJ, int tempLen, int mode, int tail)
{
	//cout << curGraph[beginI][beginJ].name << endl;
	int curTail = curGraph[beginI][beginJ].name[curGraph[beginI][beginJ].len - 1] - 'a';
	int curLen = curGraph[curTail].size();
	int i = 0;
	int edgeCount = 0;
	ifCheck[curGraph[beginI][beginJ].num] = 1;
	tempLen += (mode == 1) ? 1 : curGraph[beginI][beginJ].len;
	tempAns.push_back(curGraph[beginI][beginJ].name);
	for (i = 0; i < curLen; i++)
	{
		if (ifCheck[curGraph[curTail][i].num] == 0)
		{
			edgeCount++;
			/*if (fff == 1 && curTail == 'e' - 'a')
			{
				cout << curGraph[curTail][i].name << endl;
			}*/
			ringDFS(curTail, i, tempLen, mode, tail);


		}

	}
	/*if (DEBUG == 1)
	{
		//cout << preP.ringGraph[beginI][beginJ].name << "     " << edgeCount << endl;
	}*/
	if (tail == 0)
	{
		if (edgeCount == 0)
		{
			/*if (DEBUG == 1)
			{
				cout << tempLen << "<<temp       max>>" << letterLen << endl;
				cout << maxAns.size() << endl;
			}*/
			if (tempLen > letterLen)
			{
				maxAns = tempAns;
				letterLen = tempLen;
				UpdateOutDegree();
			}

		}
	}
	else
	{
		if (curTail + 'a' == tail)
		{
			if (tempLen > letterLen)
			{
				maxAns = tempAns;
				letterLen = tempLen;
				UpdateOutDegree();
			}
		}
	}
	ifCheck[curGraph[beginI][beginJ].num] = 0;
	tempLen -= (mode == 1) ? 1 : curGraph[beginI][beginJ].len;
	tempAns.pop_back();
}

vector <string> RingDFS::initDFS(int mode, int head, int tail, int ring)
{
	//vector <string> tempAns;
	//vector <string> maxAns;
	if (ring == 0)
	{
		curGraph = preP.graph;
	}
	else
	{
		curGraph = preP.ringGraph;
	}
	//printCurGraph();
	//preP.printRingGraph();
	ifCheck.resize(preP.ringNum);
	letterLen = 0;
	int i = 0, j = 0;
	int vecLen;
	maxAns.resize(0);
	UpdateOutDegree();
	if (head != 0 && ring == 1) {
		vecLen = curGraph[head - 'a'].size();
		for (i = 0; i < vecLen; i++)
		{
			tempAns.resize(0);
			//tempAns.push_back(preP.ringGraph[head - 'a'][i].name);

			int l = (mode == 1) ? 1 : curGraph[head - 'a'][i].len;
			ringDFS(head - 'a', i, 0, mode, tail);
		}
	}
	else
	{
		if (ring != 0)
		{
			int ifBegin = 0;
			for (i = 0; i < 26; i++)
			{
				ifBegin = 0;
				vecLen = curGraph[i].size();
				for (j = 0; j < vecLen; j++)
				{

					tempAns.resize(0);
					//tempAns.push_back(preP.ringGraph[i][j].name);

					if (int(curGraph[i].size()) > outDegree[i])
					{
						if (DEBUG == 1)
						{
							cout << "start:  " << curGraph[i][j].name << endl;
						}
						int l = (mode == 1) ? 1 : curGraph[i][j].len;
						ringDFS(i, j, 0, mode, tail);
					}

					/*if (ifExist[i][j] != 0)
					{
						ifBegin = 1;
						break;
					}*/
				}
				/*if (ifBegin == 0)
				{
					vecLen = preP.ringGraph[j].size();
					for (i = 0; i < vecLen; i++)
					{
						tempAns.resize(0);
						tempAns.push_back(preP.ringGraph[j][i].name);
						cout << "start:  " << preP.ringGraph[j][i].name << endl;
						int l = (mode == 1) ? 1 : preP.ringGraph[j][i].len;
						ringDFS(j, i, maxAns, tempAns, l, mode, tail);
					}
				}*/
			}
		}
		else
		{
			if (head != 0)
			{
				vecLen = curGraph[head - 'a'].size();
				for (i = 0; i < vecLen; i++)
				{
					tempAns.resize(0);
					//tempAns.push_back(preP.ringGraph[head - 'a'][i].name);

					int l = (mode == 1) ? 1 : curGraph[head - 'a'][i].len;
					optDFS(head - 'a', i, mode, tail);
				}
			}
			else {
				int ifBegin = 0;
				for (j = 0; j < 26; j++)
				{
					ifBegin = 0;
					vecLen = curGraph[j].size();
					//cout << char(j + 'a') << endl;
					for (i = 0; i < 26; i++)
					{
						if (preP.ifExist[i][j] != 0 && i != j)
						{
							ifBegin = 1;
							//cout << char(i + 'a') << endl;
							break;
						}
					}
					//cout << ifBegin << "\n\n" << endl;
					if (ifBegin == 0)
					{
						//cout << j << endl;
						for (i = 0; i < vecLen; i++)
						{
							tempAns.resize(0);
							//tempAns.push_back(curGraph[j][i].name);
							//cout << "start:  " << curGraph[j][i].name << endl;
							int l = (mode == 1) ? 1 : curGraph[j][i].len;
							if (i == 2)
							{
								fff = 1;
							}
							optDFS(j, i, mode, tail);
						}
					}
				}
			}

			//====================================================
			//cout << *max_element(maxRoute, maxRoute + 26) << endl;
			int originR[26];
			for (i = 0; i < 26; i++)
			{
				originR[i] = maxRoute[i];
			}
			int mI = 0, mR = -1, curH, curT, lastR, hh, tt;
			string word;
			char *wordd = (char *)malloc(12);
			for (i = 0; i < 26; i++) {
				if (maxRoute[i] > mR)
				{
					mR = maxRoute[i];
					mI = i;
				}
			}
			if (mR <= 0)
			{
				cout << "no solution" << endl;
				return maxAns;
			}
			curT = mI;
			curH = headLetter[mI];
			hh = curH;
			tt = curT;
			lastR = maxRoute[mI];
			maxRoute[mI] = -2;
			//cout << char(curH + 'a') << endl;

			while (1)
			{
				//cout << char(curT + 'a') << endl;

				for (i = 0; i < int(curGraph[curH].size()); i++)
				{
					if (curGraph[curH][i].name[curGraph[curH][i].len - 1] - 'a' == mI)
					{
						if (hh != tt)
						{
							maxAns.push_back(curGraph[curH][i].name);
						}
						hh = -1;
						tt = 1;
						curH = curT;
						break;
					}
				}
				if (preP.ifExist[curT][curT] > 0)
				{
					for (int k = 0; k < int(curGraph[curT].size()); k++)
					{
						if (curGraph[curT][k].name[curGraph[curT][k].len - 1] - 'a' == curT)
						{
							maxAns.push_back(curGraph[curT][k].name);
						}
					}


					if (originR[curT] == (mode == 1 ? 1 : preP.ifExist[curT][curT]))
					{
						break;
					}
				}
				if (originR[curT] == 0)
				{
					break;
				}
				mR = -1;
				for (i = 0; i < int(curGraph[curH].size()); i++) {
					if (maxRoute[curGraph[curH][i].name[curGraph[curH][i].len - 1] - 'a'] > mR)
					{
						curT = curGraph[curH][i].name[curGraph[curH][i].len - 1] - 'a';
						mR = maxRoute[curGraph[curH][i].name[curGraph[curH][i].len - 1] - 'a'];

					}
				}
				mI = curT;

				lastR = maxRoute[mI];
				maxRoute[mI] = -2;
			}
		}
	}

	return maxAns;
}

void RingDFS::printCurGraph() {
	int i = 0, j = 0;
	char c;
	int len;
	for (i; i < 26; i++)
	{
		c = i + 'a';
		cout << c << " Words -----------------------" << endl;
		len = curGraph[i].size();
		for (j = 0; j < len; j++)
		{
			cout << curGraph[i][j].name << endl;
		}
		cout << "================================\n\n" << endl;
	}
}



void RingDFS::optDFS(int beginI, int beginJ, int mode, int tail)
{
	//cout << curGraph[beginI][beginJ].name << endl;
	int curTail = curGraph[beginI][beginJ].name[curGraph[beginI][beginJ].len - 1] - 'a';
	int curLen = curGraph[curTail].size();
	int i = 0;
	int edgeCount = 0;
	int curRoute = 0;
	ifCheck[curGraph[beginI][beginJ].num] = 1;
	for (i = 0; i < curLen; i++)
	{
		i = i;
		if (ifCheck[curGraph[curTail][i].num] == 0)
		{
			edgeCount++;
			if (maxRoute[curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a'] == -1)
			{
				optDFS(curTail, i, mode, tail);
				curRoute = mode == 1 ? (1 + maxRoute[curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a']) : (curGraph[curTail][i].len + maxRoute[curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a']);
				if (maxRoute[curTail] < curRoute && maxRoute[curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a']>-1)
				{
					maxRoute[curTail] = curRoute;
					headLetter[curTail] = beginI;
				}
				if (maxRoute[curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a'] == -1)
				{
					Error("optDFS route not found when recursion ends");
				}
				if ((curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a') == (curTail))
				{
					selfRing[curTail] = 1;
				}
			}
			else if (maxRoute[curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a'] >= 0)
			{
				curRoute = mode == 1 ? (1 + maxRoute[curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a']) : (curGraph[curTail][i].len + maxRoute[curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a']);
				if (curTail == curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a' && selfRing[curTail] == 1)
				{

					curRoute -= mode == 1 ? (1 + maxRoute[curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a']) : (curGraph[curTail][i].len + maxRoute[curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a']);
				}
				else if (curTail == curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a' && selfRing[curTail] == 0)
				{
					selfRing[curTail] = 1;
				}
				if (maxRoute[curTail] < curRoute)
				{
					maxRoute[curTail] = curRoute;
					headLetter[curTail] = beginI;
				}
			}
		}

	}
	if (DEBUG == 1)
	{
		//cout << preP.ringGraph[beginI][beginJ].name << "     " << edgeCount << endl;
	}
	if (tail == 0)
	{
		if (edgeCount == 0)
		{
			if (DEBUG == 1)
			{
				//cout << tempLen << "<<temp       max>>" << letterLen << endl;
				//cout << maxAns.size() << endl;
			}
			maxRoute[curTail] = 0;
		}
	}
	else
	{
		if (curTail + 'a' == tail)
		{
			ifFindTail = 1;
			maxRoute[curTail] = 0;
			headLetter[curTail] = beginI;
		}
		else
		{
			if (edgeCount == 0)
			{
				ifFindTail = 0;
				maxRoute[curTail] = -2;
			}
			else
			{
				if (ifFindTail == 0 && maxRoute[curTail] == -1)
				{
					maxRoute[curTail] = -2;
				}

			}
		}
	}
	ifCheck[curGraph[beginI][beginJ].num] = 0;
	//tempLen -= (mode == 1) ? 1 : curGraph[beginI][beginJ].len;

}

void RingDFS::UpdateOutDegree()
{
	int i;
	for (i = 0; i < 26; i++)
	{
		outDegree[i] = 0;
	}
	for (i = 0; i < int(maxAns.size()); i++)
	{
		outDegree[maxAns[i][0] - 'a']++;
	}

}


PreProcess::PreProcess()
{

}
PreProcess::PreProcess(string str, int r)
{
	this->path = str;
	ring = r;
	ringGraph.resize(26);
	graph.resize(26);
	checkR.resize(26);
	for (int i = 0; i < 26; i++)
	{
		checkR[i].resize(26);
	}
	GenGraph();


}
PreProcess::PreProcess(string str, int f, char* words[], int r)
{
	int n;
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			ifExist[i][j] = 0;
		}
	}
	ring = r;
	ringGraph.resize(26);
	graph.resize(26);
	checkR.resize(26);
	for (int i = 0; i < 26; i++)
	{
		checkR[i].resize(26);
	}
	n = strToWords(str, words);
	/*for (int i = 0; i < n; i++)
	{
		cout << words[i] << endl;
	}*/
	strToVector(words);
	//printGraph();

}
PreProcess::PreProcess(char* wordss[], int len, int r)
{
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			ifExist[i][j] = 0;
		}
	}
	ring = r;
	ringGraph.resize(26);
	//cout << "22222222222222" << endl;
	graph.resize(26);
	wordn = len;
	checkR.resize(26);
	for (int i = 0; i < 26; i++)
	{
		checkR[i].resize(26);
	}
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
	int repeated = 0;
	if (!file)
	{
		Error("Input File Doesn't Exit");
	}
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			ifExist[i][j] = 0;
		}
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
			while (isalpha(temp[i]) && i < tempn)
			{
				temp[i] = tolower(temp[i]);
				i++;
			}
			node newN = { temp.substr(wordBegin, i - wordBegin), (PreProcess::ringNum)++, i - wordBegin };
			h = newN.name[0] - 'a';
			t = newN.name[i - wordBegin - 1] - 'a';
			repeated = 0;
			if (ifExist[h][t] != 0)
			{
				for (j = 0; j<int(checkR[h][t].size()); j++)
				{
					if (newN.name.compare(checkR[h][t][j]) == 0)
					{
						repeated = 1;
						break;
					}
				}
			}
			if (repeated == 0)
			{
				ringGraph[h].push_back(newN);
				checkR[h][t].push_back(newN.name);
			}

			if (ifExist[h][t] != 0 && h == t && ring == 0)
			{
				Error("Multiple Self Ring Found");
			}
			if ((i - wordBegin) > ifExist[h][t] && ifExist[h][t] != 0)
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
	if ((PreProcess::num <= 1 && ring == 0) || PreProcess::ringNum <= 1)
	{
		Error("No Word Chain in File");
	}
	for (i = 0; i < 26; i++)
	{
		sort(ringGraph[i].begin(), ringGraph[i].end(), &cmpLen);
	}
}

void PreProcess::printGraph() {
	int i = 0, j = 0;
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
	//ofstream slt("solution.txt");
	unsigned int i;
	for (i = 0; i < ary.size(); i++)
	{
		cout << ary[i] << endl;
	}
	//slt.close();
}

void PreProcess::strToVector(char* words[])
{
	int i = 0, j;
	int graphn;
	int h, t;
	int len = wordn;
	int repeated = 0;
	for (i = 0; i < len; i++)
	{
		//cout << words[i] << endl;
		string ss = words[i];
		//cout << ss << endl;
		node newN = { ss, (PreProcess::ringNum)++, int(ss.size()) };
		h = newN.name[0] - 'a';
		t = newN.name[ss.size() - 1] - 'a';

		repeated = 0;
		if (ifExist[h][t] != 0)
		{
			for (j = 0; j<int(checkR[h][t].size()); j++)
			{
				if (newN.name.compare(checkR[h][t][j]) == 0)
				{
					repeated = 1;
					break;
				}
			}
		}
		if (repeated == 0)
		{
			ringGraph[h].push_back(newN);
			checkR[h][t].push_back(ss);
		}
		if (ifExist[h][t] != 0 && h == t && ring == 0)
		{
			Error("Multiple Self Ring Found");
		}
		if (int((strlen(words[i]))) > ifExist[h][t] && ifExist[h][t] != 0)
		{

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
	/*for (i = 0; i < len; i++)
	{
		free(words[i]);
	}*/
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
	int i = 0, j = 0;
	for (i = 0; i < int(ans.size()); i++)
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
	int tempn = temp.size();
	unsigned int count = 0;
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

		const unsigned int ll = i - wordBegin;

		//strcpy_s(words[count], ll+1, word.c_str());
		for (j = 0; j < int(ll); j++)
		{
			singleWord[j] = temp[wordBegin + j];
		}
		//words[count][ll] = '\0';
		singleWord[ll] = '\0';
		words[count] = new char[ll + 1];
		//words[count] = (char *)malloc(sizeof(char) * (ll + 1));
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

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
	int debug = 0;
	if (head != 0)
	{
		head == isalpha(head) ? head : 0;
	}
	if (tail != 0)
	{
		tail == isalpha(tail) ? tail : 0;
	}
	PreProcess ppa(words, len, enable_loop);
	if (debug)
	{
		cout << "words to vector complete" << endl;
	}
	//cout << "1" << endl;
	RingDFS rd(ppa);

	DFS dfs(ppa);
	//ppa.printGraph();
	dfs.getGraph();
	dfs.hasRing(enable_loop);
	if (debug)
	{
		cout << "check ring complete" << endl;
	}
	//ppa.printRingGraph();
	vector <string> ans = rd.initDFS(1, head, tail, enable_loop);
	if (debug)
	{
		cout << "dfs complete" << endl;
	}
	ppa.VecToStr(result, ans);
	if (debug)
	{
		cout << "ans vector to result complete" << endl;
	}
	ppa.print(ans);
	if (debug)
	{
		cout << "print to txt complete" << endl;
		cout << ans.size() << endl;
	}
	/*for (int i = 0; i < len; i++)
	{
		free(words[i]);
	}*/
	int lll = int(ans.size());
	return lll;
	//return 1;
}
int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
	if (head != 0)
	{
		head == isalpha(head) ? head : 0;
	}
	if (tail != 0)
	{
		tail == isalpha(tail) ? tail : 0;
	}
	PreProcess ppa(words, len, enable_loop);
	RingDFS rd(ppa);
	DFS dfs(ppa);
	dfs.getGraph();
	dfs.hasRing(enable_loop);
	vector <string> ans = rd.initDFS(2, head, tail, enable_loop);
	ppa.VecToStr(result, ans);
	ppa.print(ans);
	/*for (int i = 0; i < len; i++)
	{
		free(words[i]);
	}*/
	int lll = int(ans.size());
	return lll;
}

