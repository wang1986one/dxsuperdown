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

	// 响应内容类型
#define HTTP_CONTENT_TYPE					_T("Content-Type")
	// 响应内容编码
#define HTTP_CONTENT_ENCODING		_T("Content-Encoding")
	// 响应内容语言
#define HTTP_CONTENT_LANGUAGE		_T("Content-Language")
	// 响应内容分段范围
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
	// 请求内容最后修改时间
#define HTTP_LAST_MODIFIED			_T("Last-Modified")
	// 请求内容地址变动
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

		/*请求属性设置*/

		void SetRequestURL(LPCTSTR szURL);	// 设置请求链接
		void SetMethod(LPCTSTR szMethod);	// 设置请求类型 "GET" "POST"
		bool SetSaveToFile(LPCTSTR szSaveFilePath,LPCTSTR szTmpFilePath=NULL);	// 设置保存的文件路径和临时文件名
		void SetRequestData(CMemBuffer bufRequestData);	// 设置POST数据
		void SetRequestHeader(LPCTSTR szKey,LPCTSTR szValue);	// 设置请求的Headers
		void SetContentBuffer(CMemBuffer* pBuffer);	// 设置外部缓冲区保存数据
		void SetNotify(HWND hNotify);	// 通知接口窗体句柄
		void SetAutoRedirect(bool bAutoRedirect);	// 是否运行自动跳转
		void SetRequestCookies(LPCTSTR szCookies);	// 设置Cookies
		void SetUserAgent(LPCTSTR szUserAgent);		// 设置UserAgent，默认为Manager指定的
		void SetProxyInfo(DWORD dwProxyType,LPCTSTR szProxyURL=NULL,LPCTSTR szProxyUserName=NULL,LPCTSTR szProxyPassword=NULL);
		void SetProxyURL(LPCTSTR szProxyURL);
		void SetUseIEProxyInfo(bool bUseIEProxyInfo=true);	// 设置使用IE代理信息，否则直连
		void SetProxyUserName(LPCTSTR szProxyUserName);	
		void SetProxyPassword(LPCTSTR szProxyPassword);
		void SetRequireValidSslCertificates(bool require);	// 要求SSL证书验证
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

		// 请求结果读取
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
		void SetResponseHeader(LPCTSTR szKey,LPCTSTR szValue);	// 设置服务器响应Headers
		CMemBuffer* GetDataBuffer(void);	// 返回具体数据缓冲区，内部OR外部
		void ProgressData(CMemBuffer* pBuffer);
		void SetStatus(DWORD dwStatus,LPCTSTR lpszError=NULL);
		void Initialize(void);
		void CloseFile(bool bError );
		void SendNotify(DWORD dwStatus,LPCTSTR strMessage);
		void SendProgress(DWORD dwProcessedSize,DWORD dwTotalSize);

	protected:
		// 请求数据
		CString m_requestURL;
		CString m_requestMethod;
		CString m_requestRefer;
		CString m_additionalRequestHeaders;
		CString m_additionalRequestCookies;
		CMemBuffer m_requestData;
		bool m_requestValidSslCertificates;
		bool m_autoRedirect;
		map<CString,CString> m_mapRequestHeader;

		// 应答数据
		UINT m_responseStatusCode;	// HTTP应答码
		CMemBuffer m_responseHeaders;	// 应答头,完整数据
		CMemBuffer m_responseContentBuffer;		// 接收数据缓冲区
		CMemBuffer* m_pResponseContentBuffer;	//外部设置数据保存缓冲区
		map<CString,CString> m_mapResponseHeader;	// 结果解析的Header
		UINT m_responseContentReceivedLength;   // Content接收总数
		UINT m_responseContentLength;				// Content内容总数

		// 代理信息
		DWORD	m_dwProxyType;
		CString m_proxyURL;
		CString m_proxyByPass;
		CString m_proxyUsername;
		CString m_proxyPassword;

		// HTTP连接信息
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
		DWORD m_dwStartTicket;				// 下载任务开始时间
		DWORD m_dwProgressNotifyTicket;// 用于控制发送进度通知间隔
		Utils::Mutex m_Mutex;

		// 文件与临时文件信息
		CString m_szSaveFilePath;
		CString m_szTmpFilePath;
		HANDLE m_hFile;

		// 超时时间
		UINT m_resolveTimeout;
		UINT m_connectTimeout;
		UINT m_sendTimeout;
		UINT m_receiveTimeout;
	};
}

