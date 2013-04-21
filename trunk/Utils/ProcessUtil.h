#pragma once

namespace Utils
{
	//杀掉指定进程
	BOOL KillProcess(LPCTSTR lpszProcessName);

	// 根据进程名找到进程ID
	// -1 没有找到
	DWORD FindProcess( LPCTSTR lpszProcessName );

	// 根据PID获得进程句柄
	HANDLE GetProcessHandleByPID(int nPID);

	// 根据PID获得进程名
	CString GetProcessNameByPID(int nPID);

	// 根据PID获得程序全路径
	CString GetProcessFullPath(DWORD dwProcessID);

	// 创建进程
	BOOL RunExe(LPCTSTR lpExe, LPCTSTR lpParam, DWORD* pdwExitCode,BOOL bRequiredAdmin =FALSE , BOOL bWaitExitCode = FALSE);

	// 判断当前进程是否64位
	BOOL IsWow64Process();

	// 判断指定进程是否64位
	BOOL GetProcessIsWow64(HANDLE hProcess);
}