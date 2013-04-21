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

		// �����첽HTTP����
		UINT	SendAsyncRequest(HttpRequest* pRequest);

		// ����ͬ��HTTP����
		UINT	SendRequest(HttpRequest* pRequest);

		// �ȴ�HTTP����ֱ����ʱ
		// pRequest					HTTP�������
		// dwTimedout				��ʱʱ��
		BOOL	WaitRequest(HttpRequest* pRequest,DWORD dwTimedout=INFINITE);

		BOOL	WaitAllRequest(DWORD dwTimedout=INFINITE);

		// ��ָֹ���첽HTTP����
		// pRequest					HTTP�������
		// bDeleteTempFile		�Ƿ�ɾ����ʱ�ļ�
		BOOL	CancelRequest(HttpRequest* pRequest,BOOL bDeleteTempFile=FALSE);

		// ��ֹ���ж����е��첽HTTP����
		// bDeleteTempFile		�Ƿ�ɾ����ʱ�ļ�
		void	StopAllRequest(BOOL bDeleteTempFile=FALSE,DWORD dwWaitTimes=INFINITE);

		// ��ѯָ��HTTP�������
		// UINT serial		HTTP������ˮ��
		// pProgress			����ֵָ��
		// pReceivedSize	����������ָ��
		// pTotalSize			������ָ��
		BOOL GetProgress(UINT serial,float* pProgress=NULL,DWORD* pReceivedSize=NULL,DWORD* pTotalSize=NULL);

	private:
		void RemoveWorker(HttpRequest* pRequest);	// ��ָ���������������Ƴ���������ɶ���

	private:
		UINT m_SerialSeed;
		Utils::Mutex m_Mutex;
		CString m_UserAgent;
		CString m_IEProxyURL;
		CString m_IEProxyBypass;
		list<HttpRequest*> m_listThreadQueue;	// ��������
		static UINT CALLBACK WorkerThread(LPVOID pParam);
	};
}

