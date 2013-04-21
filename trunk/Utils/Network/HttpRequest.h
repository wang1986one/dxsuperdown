#pragma once
#include <Windows.h>
#include <atlstr.h>
#include <tchar.h>
#include <map>

#include "Utils/Utils.h"
#include "Utils/MemBuffer.h"
#include "Utils/Network/NetworkUtils.h"
#include "Utils/Network/WinHttp.h"

#pragma comment(lib, "winhttp.lib")
using namespace std;

namespace Utils
{
#define HTTP_GET		_T("GET")
#define HTTP_POST		_T("POST")
#define HTTP_UTF8		_T("utf-8")

	// ��Ӧ��������
#define HTTP_CONTENT_TYPE					_T("Content-Type")
	// ��Ӧ���ݱ���
#define HTTP_CONTENT_ENCODING		_T("Content-Encoding")
	// ��Ӧ��������
#define HTTP_CONTENT_LANGUAGE		_T("Content-Language")
	// ��Ӧ���ݷֶη�Χ
#define HTTP_CONTENTRANGE				_T("Content-Range")

#define HTTP_CONNECTION					_T("Connection")
#define HTTP_CLOSE								_T("close")
#define HTTP_KEEP_ALIVE						_T("keepalive")

#define HTTP_ACCEPT						_T("Accept")
#define HTTP_ACCEPT_CHARSET		_T("Accept-Charset")
#define HTTP_ACCEPT_Language		_T("Accept-Language")
#define HTTP_CHARSET					_T("Charset")

#define HTTP_COOKIE						_T("Cookie")
#define HTTP_SET_COOKIE				_T("Set-Cookie")
#define HTTP_EXPIRES						_T("Expires")
	// ������������޸�ʱ��
#define HTTP_LAST_MODIFIED			_T("Last-Modified")
	// �������ݵ�ַ�䶯
#define HTTP_LOCATION					_T("Location")
#define HTTP_CACHE_CONTROL		_T("Cache-Control")
#define HTTP_MAX_AGE					_T("max-age")
#define HTTP_NO_CACHE				_T("no-cache")
#define HTTP_PRAGMA					_T("Pragma")
#define HTTP_RANGE						_T("Range")
#define HTTP_REFERER						_T("Referer")

	enum _enHttpStatus
	{
		HTTP_UNKNOW=0,
		HTTP_OPEN_SESSION,
		HTTP_SET_OPTIONS,
		HTTP_CONNECT,
		HTTP_OPEN_REQUEST,
		HTTP_SEND_REQUEST,
		HTTP_SEND_DATA,
		HTTP_RECV_RESPONSE,
		HTTP_RECV_DATA,
		HTTP_FINISHED,
		HTTP_PROGRESS,
		HTTP_ERROR,
		HTTP_PROXY_DIRECT,
		HTTP_PROXY_USER,
		HTTP_PROXY_IE
	};

	class HttpRequest
	{
		friend class HttpManager;
	public:
		HttpRequest(void);
		HttpRequest(LPCTSTR lpMethod,LPCTSTR lpURL,CMemBuffer bufRequestData=NULL,HWND hNotify=NULL);
		virtual ~HttpRequest(void);

		/*������������*/

		void SetRequestURL(LPCTSTR szURL);	// ������������
		void SetMethod(LPCTSTR szMethod);	// ������������ "GET" "POST"
		bool SetSaveToFile(LPCTSTR szSaveFilePath,LPCTSTR szTmpFilePath=NULL);	// ���ñ�����ļ�·������ʱ�ļ���
		void SetRequestData(CMemBuffer bufRequestData);	// ����POST����
		void SetRequestHeader(LPCTSTR szKey,LPCTSTR szValue);	// ���������Headers
		void SetContentBuffer(CMemBuffer* pBuffer);	// �����ⲿ��������������
		void SetNotify(HWND hNotify);	// ֪ͨ�ӿڴ�����
		void SetAutoRedirect(bool bAutoRedirect);	// �Ƿ������Զ���ת
		void SetRequestCookies(LPCTSTR szCookies);	// ����Cookies
		void SetUserAgent(LPCTSTR szUserAgent);		// ����UserAgent��Ĭ��ΪManagerָ����
		void SetProxyInfo(DWORD dwProxyType,LPCTSTR szProxyURL=NULL,LPCTSTR szProxyUserName=NULL,LPCTSTR szProxyPassword=NULL);
		void SetProxyURL(LPCTSTR szProxyURL);
		void SetUseIEProxyInfo(bool bUseIEProxyInfo=true);	// ����ʹ��IE������Ϣ������ֱ��
		void SetProxyUserName(LPCTSTR szProxyUserName);	
		void SetProxyPassword(LPCTSTR szProxyPassword);
		void SetRequireValidSslCertificates(bool require);	// Ҫ��SSL֤����֤
		void SetUserInfo(LPVOID pParam);
		void SetTimeouts(
			UINT resolveTimeout = 0,
			UINT connectTimeout = 60000,
			UINT sendTimeout = 30000,
			UINT receiveTimeout = 30000);

		UINT		GetSerial(void);
		CString GetRequestURL(void);
		CString GetMethod(void);
		HWND		GetNotify(void);
		CMemBuffer&	GetRequestData(void);
		CString GetRequestCookies(void);
		CString GetRequestHeader(LPCTSTR szKey);
		CString GetRequestHeaders(void);
		CString GetUserAgent(void);
		CString GetProxyUserName(void);
		CString GetProxyPassword(void);
		LPVOID	GetUserInfo(void);
		UINT	GetResolveTimedout(void);
		UINT	GetConnectTimedout(void);
		UINT	GetSendTimedout(void);
		UINT	GetReceiveTimedout(void);

		// ��������ȡ
		UINT	GetResponseStatusCode(void);
		CString GetRequestHost(void);
		CString GetResponseCharset(void);
		CString GetResponseLocation(void);
		CString GetResponseHeader(LPCTSTR lpszKey);
		CString GetResponseHeaders(void);
		CString GetCookies(void);
		CMemBuffer& GetResponseContent(void);

		DWORD GetLastError(void);
	private:
		HttpRequest(const HttpRequest& other);
		HttpRequest &operator =(const HttpRequest& other);
		void SetResponseHeader(LPCTSTR szKey,LPCTSTR szValue);	// ���÷�������ӦHeaders
		CMemBuffer* GetDataBuffer(void);	// ���ؾ������ݻ��������ڲ�OR�ⲿ
		void ProgressData(CMemBuffer* pBuffer);
		void SetStatus(DWORD dwStatus,LPCTSTR lpszError=NULL);
		void Initialize(void);
		void CloseFile(bool bError );
		void SendNotify(DWORD dwStatus,LPCTSTR strMessage);
		void SendProgress(DWORD dwProcessedSize,DWORD dwTotalSize);

	protected:
		// ��������
		CString m_requestURL;
		CString m_requestMethod;
		CString m_requestRefer;
		CString m_additionalRequestHeaders;
		CString m_additionalRequestCookies;
		CMemBuffer m_requestData;
		bool m_requestValidSslCertificates;
		bool m_autoRedirect;
		map<CString,CString> m_mapRequestHeader;

		// Ӧ������
		UINT m_responseStatusCode;	// HTTPӦ����
		CMemBuffer m_responseHeaders;	// Ӧ��ͷ,��������
		CMemBuffer m_responseContentBuffer;		// �������ݻ�����
		CMemBuffer* m_pResponseContentBuffer;	//�ⲿ�������ݱ��滺����
		map<CString,CString> m_mapResponseHeader;	// ���������Header
		UINT m_responseContentReceivedLength;   // Content��������
		UINT m_responseContentLength;				// Content��������

		// ������Ϣ
		DWORD	m_dwProxyType;
		CString m_proxyURL;
		CString m_proxyByPass;
		CString m_proxyUsername;
		CString m_proxyPassword;

		// HTTP������Ϣ
		UINT	m_Serial;
		HttpManager* m_pManager;
		HANDLE m_hThreadHandle;
		DWORD m_dwThreadID;
		bool m_IsURLValid;
		CString m_requestHost;
		CString m_requestURLPath;
		INTERNET_PORT m_requestPort;
		CString m_requestUserName;
		CString m_requestPassword;
		CString m_userAgent;
		CString m_szErrorString;
		HINTERNET m_hSession;
		HINTERNET m_hConnect;
		HINTERNET m_hRequest;
		bool m_requestIsHTTPS;
		HWND m_hNotify;
		DWORD m_dwLastError;
		LPVOID m_dwUserInfo;
		DWORD m_requestStatusCode;
		DWORD m_dwStartTicket;				// ��������ʼʱ��
		DWORD m_dwProgressNotifyTicket;// ���ڿ��Ʒ��ͽ���֪ͨ���
		Utils::Mutex m_Mutex;

		// �ļ�����ʱ�ļ���Ϣ
		CString m_szSaveFilePath;
		CString m_szTmpFilePath;
		HANDLE m_hFile;

		// ��ʱʱ��
		UINT m_resolveTimeout;
		UINT m_connectTimeout;
		UINT m_sendTimeout;
		UINT m_receiveTimeout;
	};
}

