// clsSec.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"

TclsSec *cls=NULL;
void *addr;
DWORD (WINAPI *oRegisterClassA)(WNDCLASSA *lpWndClass);
DWORD WINAPI nRegisterClassA(WNDCLASSA *lpWndClass){
	char *p=(char*)lpWndClass->lpszClassName;
	lpWndClass->lpszClassName=cls->check(p);
	return oRegisterClassA(lpWndClass);
}
void* __fastcall setHook(void *src,void *des,int sz){
	char pt[5],*jmp=(char*)malloc(sz+5);
	memcpy(jmp,src,sz);
	jmp+=sz;
	pt[0]=jmp[0]=(char)0xE9;
	*(long*)&pt[1]=(long)des-((long)src+5);
	*(long*)&jmp[1]=(long)src+sz-((long)jmp+5);
	SIZE_T r;
	WriteProcessMemory((HANDLE)-1,src,pt,5,&r);
	VirtualProtectEx((HANDLE)-1,jmp,sz,PAGE_EXECUTE_READWRITE,&r); 
	return jmp-sz;
}
int WINAPI clsSec_Start(){
	if(oRegisterClassA)
		return 0;
	addr=GetProcAddress(LoadLibrary("user32"),"RegisterClassA");
	*(void**)&oRegisterClassA=setHook(
		addr,nRegisterClassA,5
	);
	return 1;
}
int WINAPI clsSec_Hook(char *onm,char *nnm){
	return cls->hook(onm,nnm);
}
void WINAPI clsSec_ErrLook(int code){
	cls->err_look(code);
}
int WINAPI clsSec_GenRnd(char *p,int sz){
	return cls->gen_rnd(p,sz);
}
void WINAPI clsSec_Destroy(){
	SIZE_T r;
	WriteProcessMemory((HANDLE)-1,addr,oRegisterClassA,5,&r);
	delete cls;
	cls=NULL;
}
void* WINAPI clsSec(){
	if(!cls)
		cls=new TclsSec;
	return cls;
}
#ifdef DLLATTACH
void clsSec_DllAttach(){
	char buf[300];
	stringstream ss;
	GetModuleFileName(NULL,buf,MAX_PATH);
	for(int i=strlen(buf);i>0;i--){
		if(buf[i]=='\\'){
			buf[++i]='\0';
			ss<<buf<<"clsSec.ini";
			break;
		}
	}
	Tini ini(ss.str(),"clsSec");
	cls=new TclsSec;
	for(int i=0;i<1000;i++){
		string k,v,s=ini.get(i);
		int len=s.length();
		if(len){
			len++;
			memcpy(buf,s.c_str(),len);
			for(int x=0;x<len;x++){
				if(buf[x]==','){
					buf[x]='\0';
					v=&buf[++x];
					break;
				}
			}
			k=buf;
			cls->hook(k,v);
		}else{
			break;
		}
	}
	clsSec_Start();
}
#endif
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
#ifdef DLLATTACH
	if(ul_reason_for_call==DLL_PROCESS_ATTACH){
		//通过导入表注入修改类名
		clsSec_DllAttach();
	}
#endif
    return TRUE;
}
