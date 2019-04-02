// GxxGmApiSpyEx.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "GxxGmApiSpyEx.h"

#include "../../minhook/include/MinHook.h"
#if defined _M_X64
#pragma comment(lib, "../../minhook/build/VC12/lib/Debug/libMinHook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "../../minhook/build/VC12/lib/Debug/libMinHook.x86.lib")
#endif

int InitializeHook()
{
	MH_STATUS status = MH_Initialize();
	if (status != MH_OK)
	{
		return 0;
	}
	return 0;
}


