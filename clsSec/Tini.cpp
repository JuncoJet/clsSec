#include "StdAfx.h"
#include "Tini.h"

string Tini::get(string k){
	char buf[300];
	GetPrivateProfileString(app.c_str(),k.c_str(),"",buf,300,file.c_str());
	return buf;
}
string Tini::get(int k){
	stringstream ss;
	ss<<k;
	return get(ss.str());
}
Tini::Tini(string file,string app){
	this->file=file;
	this->app=app;
}