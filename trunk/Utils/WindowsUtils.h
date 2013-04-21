#pragma once
#include <vector>

namespace Utils
{
	// �жϵ�ǰϵͳ�Ƿ�64λ
	BOOL IsWow64OS();

	BOOL IsRunAsAdministrator();

	// ���ϵͳ�汾
	// 0x0500 Win2000
	// 0x0501 XP
	// 0x0600 Vista
	// 0x0601 Win7
	int GetWinVer();

	// ��ǰϵͳ�Ƿ���Vista������
	BOOL IsAboveXP();

	// Vista Win7ע��ȫ����Ϣ
	// uMessageID WM_MESSAGE_ID
	// bAllow ��ӻ�ɾ��
	BOOL AllowMeesageForVistaAbove(UINT uMessageID, BOOL bAllow);

	// ����Ȩ��
	// szPrivName ��Ҫ���õ�Ȩ���ַ��� SE_DEBUG_NAME
	BOOL EnablePrivilege(LPCTSTR szPrivName);

	class CFileVersion
	{
		// Construction  
	public:   
		CFileVersion();  
		~CFileVersion();

		// Operations     
	public:   
		BOOL    Open(LPCTSTR lpszModuleName); 
		BOOL    Open(DWORD dwProcessID); 

		void    Close();  

		CString GetFileDescription();
		CString GetFileVersion();
		CString GetInternalName();
		CString GetCompanyName();
		CString GetLegalCopyright();
		CString GetOriginalFilename();
		CString GetProductName(); 
		CString GetProductVersion();
		CString GetFixedFileVersion();  
		CString GetFixedProductVersion();

	private:
		CString QueryValue(LPCTSTR lpszValueName, DWORD dwLangCharset = 0);
		BOOL    GetFixedInfo(VS_FIXEDFILEINFO& vsffi);

	protected:
		// Attributes  
		LPBYTE  m_lpVersionData;   
		DWORD   m_dwLangCharset;   
	};

	class OSInfo
	{
	public:
		OSInfo(){}
		CString ProductName;			// Windows 8 Pro
		CString EditionID;					// Professional
		CString CurrentVersion;		// 6.2
		CString CurrentBuild;			// 9200
	};

	OSInfo GetOSInfo();//��ȡϵͳ��Ϣ

	class FlashInfo
	{
	public:
		CString ActiveXPath;				// C:\Windows\System32\Macromed\Flash\Flash.ocx
		CString ActiveXVersion;		// 11.3.377.15
		CString PluginPath;				// C:\Windows\system32\Macromed\Flash\NPSWF64_11_5_502_135.dll
		CString PluginVersion;			// 11.5.502.135
		CString CurrentVersion;		// ��ǰ����汾
	};

	FlashInfo GetFlashInfo();

	class IEInfo
	{
	public:
		CString Version;
		CString Build;
		CString svcUpdateVersion;
		CString svcVersion;
	};

	IEInfo GetIEInfo();

}