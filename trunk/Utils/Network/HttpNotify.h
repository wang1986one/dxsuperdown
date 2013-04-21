#pragma once
#include "Utils/Network/HttpRequest.h"

namespace Utils
{
	typedef struct _stHttpNotify
	{
		HttpRequest* pRequest;
		double fPercent;
		DWORD dwProcessedSize;
		DWORD dwTotalSize;
		CString szErrorMessage;
	}HttpNotify,*PHttpNotify;

	static DWORD WM_HTTP_NOTIFY=::RegisterWindowMessage(_T("WinHTTPNotify"));
	
	class IHttpNotify
	{
	public:

		//��Ϣ֪ͨ�ӿڣ��ַ�Http�¼�
		virtual void OnHttpNotify(WPARAM wParam,LPARAM lParam);

		//	HTTP����״̬�仯֪ͨ
		// pRequest					��Ϣ����
		// dwStatus					HTTP��״̬
		virtual void OnHttpStatusChanged(HttpRequest* pRequest,DWORD dwStatus);

		//	HTTP�������
		// pRequest					��Ϣ����
		// bSuccessed				HTTP�����Ƿ������󣬳�ʱ
		virtual void OnHttpFinished(HttpRequest* pRequest,BOOL bSuccessed);

		// ����֪ͨ
		// pRequest					��Ϣ����
		// fFinishedPercent		������ɰٷֱ�
		// dwReceivedSize		�ѽ��մ�С
		// dwTotalSize				�ܴ�С
		virtual void OnHttpProgress(
			HttpRequest* pRequest,
			double fFinishedPercent,
			DWORD dwReceivedSize,
			DWORD dwTotalSize
			);
	};
}

