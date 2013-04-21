#pragma once
#ifndef Utils_h__
#define Utils_h__

#include "ThreadUtil.h"
#include "FileUtil.h"
#include "StringUtil.h"
#include <vector>
#include <map>

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) { if (x) { x->Release(); x = NULL; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { delete x; x = NULL; }
#endif

#ifdef _DEBUG
	#ifndef TRACE
		#define TRACE Utils__Trace
	#endif
#else
	#ifndef TRACE
		#define TRACE
	#	endif
#endif

namespace Utils
{
	typedef std::vector<CString> VString;
	typedef std::map<CString,CString> MString;
}

extern void Utils__Trace( LPCTSTR pstrFormat, ... );
extern void Utils__TraceFile( LPCTSTR pstrFormat, ... );

#endif // Utils_h__

