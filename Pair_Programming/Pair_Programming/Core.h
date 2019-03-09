#pragma once
#include "pch.h"
#include <iostream>
#include "Input.h"
#include "PreProcess.h"
#include "DFS.h"
#include <string>
#include <vector>
#include "RingDFS.h"

using namespace std;

class Core
{
public:
	Core();
	~Core();
	int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
	int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
};

