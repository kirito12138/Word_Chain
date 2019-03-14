#include "pch.h"
#include "RingDFS.h"
#include <string>
#include <vector>
#include "Error.h"
#include "PreProcess.h"
#include <stdlib.h>
#include <algorithm>

#define DEBUG 0
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
	tempLen += (mode == 1) ? 1: curGraph[beginI][beginJ].len;
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
	tempLen -= (mode == 1) ? 1: curGraph[beginI][beginJ].len;
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
			int mI=0, mR=-1, curH, curT, lastR, hh, tt;
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

					
					if (originR[curT] == (mode==1?1:preP.ifExist[curT][curT]))
					{
						break;
					}
				}
				if (originR[curT] == 0 )
				{
					break;
				}
				mR = -1;
				for (i = 0; i < int(curGraph[curH].size()); i++) {
					if (maxRoute[curGraph[curH][i].name[curGraph[curH][i].len -1] -'a'] > mR )
					{
						curT = curGraph[curH][i].name[curGraph[curH][i].len -1] - 'a';
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
				curRoute = mode == 1 ? (1 + maxRoute[curGraph[curTail][i].name[curGraph[curTail][i].len-1] -'a']) : (curGraph[curTail][i].len + maxRoute[curGraph[curTail][i].name[curGraph[curTail][i].len - 1] - 'a']);
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