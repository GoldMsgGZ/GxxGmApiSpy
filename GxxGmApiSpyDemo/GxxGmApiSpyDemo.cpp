// GxxGmApiSpyDemo.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "../../minhook/include/MinHook.h"

#if defined _M_X64
#pragma comment(lib, "../../minhook/build/VC12/lib/Debug/libMinHook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "../../minhook/build/VC12/lib/Debug/libMinHook.x86.lib")
#endif


// ����WindowsIP����ԭ��
typedef int (WINAPI *MESSAGEBOXW)(HWND, LPCWSTR, LPCWSTR, UINT);

// ����һ������ָ�����ڱ���ԭʼ������ַ
MESSAGEBOXW fpMessageBoxW = NULL;

// ���Ӻ��������ڸ���ԭ����
int WINAPI DetourMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
	return fpMessageBoxW(hWnd, L"Hooked!", lpCaption, uType);
}


void Original_Hook()
{
	// ��ʼ��
	MH_STATUS status = MH_Initialize();
	if (status != MH_OK)
	{
		std::cout << "Initialize Hook Engine failed. status : " << status << std::endl;
		return 0;
	}

	// 
	if (MH_CreateHook(&MessageBoxW, &DetourMessageBoxW, reinterpret_cast<void**>(&fpMessageBoxW)) != MH_OK)
	{
		return 1;
	}

	// Enable the hook for MessageBoxW.
	if (MH_EnableHook(&MessageBoxW) != MH_OK)
	{
		return 1;
	}

	// Expected to tell "Hooked!".
	MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

	// Disable the hook for MessageBoxW.
	if (MH_DisableHook(&MessageBoxW) != MH_OK)
	{
		return 1;
	}

	// Expected to tell "Not hooked...".
	MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);


	status = MH_Uninitialize();
}

int _tmain(int argc, _TCHAR* argv[])
{
	

	return 0;
}

