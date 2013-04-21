#pragma once

namespace Utils
{
	//ɱ��ָ������
	BOOL KillProcess(LPCTSTR lpszProcessName);

	// ���ݽ������ҵ�����ID
	// -1 û���ҵ�
	DWORD FindProcess( LPCTSTR lpszProcessName );

	// ����PID��ý��̾��
	HANDLE GetProcessHandleByPID(int nPID);

	// ����PID��ý�����
	CString GetProcessNameByPID(int nPID);

	// ����PID��ó���ȫ·��
	CString GetProcessFullPath(DWORD dwProcessID);

	// ��������
	BOOL RunExe(LPCTSTR lpExe, LPCTSTR lpParam, DWORD* pdwExitCode,BOOL bRequiredAdmin =FALSE , BOOL bWaitExitCode = FALSE);

	// �жϵ�ǰ�����Ƿ�64λ
	BOOL IsWow64Process();

	// �ж�ָ�������Ƿ�64λ
	BOOL GetProcessIsWow64(HANDLE hProcess);
}