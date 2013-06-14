#pragma once

// 编译环境：VS 2008 SP1 以上
// 运行环境：XP SP3 以上
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

// 依赖：
// 1. Duilib https://code.google.com/p/duilib/

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NON_CONFORMING_SWPRINTFS
//////////////////////////////////////////////////////////////////////////
// 系统库
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
#		 pragma comment(lib,"DxUtils_ud.lib")
#   else
#       pragma comment(lib, "DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "DuiLib_u.lib")
#		 pragma comment(lib,"DxUtils_u.lib")
#   else
#       pragma comment(lib, "DuiLib.lib")
#   endif
#endif

//////////////////////////////////////////////////////////////////////////
//	 DxUtils 一些辅助函数类
#include "Utils/Utils.h"
#include "Utils/StringUtil.h"
#include "Utils/Delegate.h"
#include "Utils/Network/HttpManager.h"
#pragma comment(lib,"ws2_32")
using namespace Utils;

//////////////////////////////////////////////////////////////////////////
// 全局定义
#include "Model/MessageID.h"
#include "Model/MenuID.h"

//////////////////////////////////////////////////////////////////////////
// Parser
#include "Parser/IParser.h"

