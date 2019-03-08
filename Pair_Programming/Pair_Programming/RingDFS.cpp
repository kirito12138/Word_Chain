#include "pch.h"
#include "RingDFS.h"
#include <string>
#include <vector>
#include "Error.h"
#include "PreProcess.h"

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
}

void RingDFS::ringDFS(int beginI, int beginJ, vector <string> maxAns, vector <string> tempAns, int tempLen, int mode, int tail)
{
	int curTail = preP.ringGraph[beginI][beginJ].name[preP.ringGraph[beginI][beginJ].len - 1] - 'a';
	int curLen = preP.ringGraph[curTail].size();
	int i = 0;
	int edgeCount = 0;
	ifCheck[preP.ringGraph[beginI][beginJ].num] = 1;
	tempLen += (mode == 1) ? 1:preP.ringGraph[beginI][beginJ].len;
	tempAns.push_back(preP.ringGraph[beginI][beginJ].name);
	for (i = 0; i < curLen; i++)
	{
		if (ifCheck[preP.ringGraph[curTail][i].num] == 0)
		{
			edgeCount++;
			ringDFS(curTail, i, maxAns, tempAns, tempLen, mode, tail);
		}
	}
	if (tail == 0)
	{
		if (edgeCount == 0)
		{
			if (tempLen > letterLen)
			{
				maxAns = tempAns;
				letterLen = tempLen;
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
			}
		}
	}
	ifCheck[preP.ringGraph[beginI][beginJ].num] = 0;
	tempLen -= (mode == 1) ? 1:preP.ringGraph[beginI][beginJ].len;
	tempAns.pop_back();
}

vector <string> RingDFS::initDFS(int mode, int head, int tail, int ring)
{
	vector <string> tempAns;
	vector <string> maxAns;
	ifCheck.resize(preP.ringNum);
	letterLen = 0;
	int i = 0, j = 0;
	int vecLen;
	maxAns.resize(0);
	if (head != 0) {
		vecLen = preP.ringGraph[head - 'a'].size();
			for (i = 0; i < vecLen; i++)
			{
				tempAns.resize(0);
				tempAns.push_back(preP.ringGraph[head - 'a'][i].name);
				int l = (mode == 1) ? 1 : preP.ringGraph[head - 'a'][i].len;
				ringDFS(head - 'a', i, maxAns, tempAns, l, mode, tail);
			}
	}
	else
	{
		int ifBegin = 0;
		for (j = 0; j < 26; j++) 
		{
			ifBegin = 0;
			for (i = 0; i < 26; i++)
			{
				if (ifExist[i][j] != 0)
				{
					ifBegin = 1;
					break;
				}
			}
			if (ifBegin == 0)
			{
				vecLen = preP.ringGraph[j].size();
				for (i = 0; i < vecLen; i++)
				{
					tempAns.resize(0);
					tempAns.push_back(preP.ringGraph[j][i].name);
					int l = (mode == 1) ? 1 : preP.ringGraph[j][i].len;
					ringDFS(j, i, maxAns, tempAns, l, mode, tail);
				}
			}
		}
	}
	return maxAns;
}