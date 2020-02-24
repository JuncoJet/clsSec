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
		dic[onm]=nnm;
	}else{
		new_seed();
		stringstream ss;
		for(int i=0;i<8+rand()%(50-8);i++){
			ss<<tpl[rand()%64];
		}
		dic[onm]=ss.str();
	}
	return 0;
}
int TclsSec::hook(string onm,string nnm){
	return hook(onm,(char*)nnm.c_str());
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
	hash_map<string,string>::iterator it;
	it=dic.find(nm);
	if(it!=dic.end()){
#ifdef FOR_ELNG
		SIZE_T r;
		WriteProcessMemory((HANDLE)-1,nm,it->second.c_str(),it->second.length()+1,&r);
#else
		return (char*)it->second.c_str();
#endif
	}
	return nm;
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