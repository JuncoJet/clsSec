#pragma once
#include "stdafx.h"
using namespace std;
using namespace stdext;

class TclsSec{
	int seed;
	char tpl[65];
	hash_map<string,string> dic;
	void new_seed();
	void msgbox(string msg);
public:
	char* check(char *nm);
	int gen_rnd(char *p,int sz);
	void err_look(int code);
	int hook(string onm,char *nnm);
	TclsSec(void);
	~TclsSec(void);
};
