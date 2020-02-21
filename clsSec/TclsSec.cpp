#include "stdafx.h"
#include "TclsSec.h"

TclsSec::TclsSec(void){
	char t[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	memcpy(tpl,t,sizeof(tpl));
}
TclsSec::~TclsSec(void){
	
}
int TclsSec::hook(string onm,char *nnm){
	if(nnm){
		dic.insert(pair<string,string>(onm,nnm));
	}else{
		new_seed();
		stringstream ss;
		for(int i=0;i<8+rand()%(50-8);i++){
			ss<<tpl[rand()%64];
		}
		dic.insert(pair<string,string>(onm,ss.str()));
	}
	return 0;
}
void TclsSec::new_seed(){
	if(!seed){
		seed=GetTickCount();
	}else{
		seed+=GetTickCount();
	}
	srand(seed);
}
void TclsSec::err_look(int code){
	switch (code){

	}
}
void TclsSec::msgbox(string msg){
	MessageBox(0,msg.c_str(),"clsSec",0);
}
char* TclsSec::check(char *nm){
	map<string,string>::iterator it;
	it=dic.find(nm);
	if(it!=dic.end()){
		return (char*)it->second.c_str();
	}else{
		return nm;
	}
}
int TclsSec::gen_rnd(char *p,int sz){
	new_seed();
	stringstream ss;
	for(int i=0;i<8+rand()%(50-8);i++){
		ss<<tpl[rand()%64];
	}
	int ssz=ss.str().length();
	ssz=ssz>sz?sz:ssz;
	memcpy(p,ss.str().c_str(),ssz);
	p[ssz+1]='\0';
	return ssz;
}