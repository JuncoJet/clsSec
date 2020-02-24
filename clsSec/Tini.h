#pragma once
#include "stdafx.h"

class Tini
{
	string file,app;
public:
	string get(string k);
	string get(int k);
	Tini(string file,string app);
};
