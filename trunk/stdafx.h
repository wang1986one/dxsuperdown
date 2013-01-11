#pragma once

// ���뻷����VS 2008 SP1 ����
// ���л�����XP SP3 ����
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

// ������
// 1. Duilib https://code.google.com/p/duilib/

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS
//////////////////////////////////////////////////////////////////////////
// ϵͳ��
#include <windows.h>
#include <ShellAPI.h>
#include <atlstr.h>
#include <tchar.h>
#include <string>

//////////////////////////////////////////////////////////////////////////
// Duilib
#include "DuiLib/UIlib.h"
using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif


