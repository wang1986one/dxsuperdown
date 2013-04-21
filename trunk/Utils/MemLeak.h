#if defined(_DEBUG) && !defined(__AFX_H__)
/*
usage:

Stdafx.cpp定义如下

#ifdef _DEBUG
#include "Utils\MemLeak.h"
CMemLeak g_MemLeak;
#endif

需要内存检查的cpp定义如下

#ifdef _DEBUG
#include <Utils\MemLeak.h>
#define new DEBUG_NEW
#endif

*/
#pragma once

void* __cdecl operator new(size_t nSize, LPCSTR lpszFileName, int nLine);
#ifdef DEBUG_NEW
#undef DEBUG_NEW
#endif
#define DEBUG_NEW new(__FILE__, __LINE__)
//对于 PLACEMENT NEW 尚不能支持

void* __cdecl operator new[](size_t nSize, LPCSTR lpszFileName, int nLine);

void __cdecl operator delete(void* p);

void __cdecl operator delete(void* p, LPCSTR lpszFileName, int nLine);

void __cdecl operator delete[](void *p);

void __cdecl operator delete[](void* p, LPCSTR lpszFileName, int nLine);

class CMemLeak
{
public:
	CMemLeak(void);

	~CMemLeak(void);
};
#endif