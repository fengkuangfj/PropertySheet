// dllmain.cpp : DllMain ��ʵ�֡�

#include "stdafx.h"
#include "resource.h"
#include "MyPropertySheet_i.h"
#include "dllmain.h"

CMyPropertySheetModule	_AtlModule;
LONG					g_lLockCnt = 0;

// DLL ��ڵ�
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	g_lLockCnt = _AtlModule.m_nLockCnt;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
