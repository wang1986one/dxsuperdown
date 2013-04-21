#pragma once
#include <list>
#include "Utils/Network/HttpRequest.h"

namespace Utils
{
	static CString szAgent = L"Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.17 (KHTML, like Gecko) Chrome/24.0.1312.52 Safari/537.17";
	using std::list;

	class HttpManager
	{
	public:
		HttpManager(void);

		// 发送异步HTTP请求
		UINT	SendAsyncRequest(HttpRequest* pRequest);

		// 发送同步HTTP请求
		UINT	SendRequest(HttpRequest* pRequest);

		// 等待HTTP请求直到超时
		// pRequest					HTTP请求对象
		// dwTimedout				超时时间
		BOOL	WaitRequest(HttpRequest* pRequest,DWORD dwTimedout=INFINITE);

		BOOL	WaitAllRequest(DWORD dwTimedout=INFINITE);

		// 终止指定异步HTTP请求
		// pRequest					HTTP请求对象
		// bDeleteTempFile		是否删除临时文件
		BOOL	CancelRequest(HttpRequest* pRequest,BOOL bDeleteTempFile=FALSE);

		// 终止所有队列中的异步HTTP请求
		// bDeleteTempFile		是否删除临时文件
		void	StopAllRequest(BOOL bDeleteTempFile=FALSE,DWORD dwWaitTimes=INFINITE);

		// 查询指定HTTP请求进度
		// UINT serial		HTTP请求流水号
		// pProgress			进度值指针
		// pReceivedSize	已下载数据指针
		// pTotalSize			总数据指针
		BOOL GetProgress(UINT serial,float* pProgress=NULL,DWORD* pReceivedSize=NULL,DWORD* pTotalSize=NULL);

	private:
		void RemoveWorker(HttpRequest* pRequest);	// 将指定请求从任务队列移出，加入完成队列

	private:
		UINT m_SerialSeed;
		Utils::Mutex m_Mutex;
		CString m_UserAgent;
		CString m_IEProxyURL;
		CString m_IEProxyBypass;
		list<HttpRequest*> m_listThreadQueue;	// 工作任务
		static UINT CALLBACK WorkerThread(LPVOID pParam);
	};
}

