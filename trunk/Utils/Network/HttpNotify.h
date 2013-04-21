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

		//消息通知接口，分发Http事件
		virtual void OnHttpNotify(WPARAM wParam,LPARAM lParam);

		//	HTTP请求状态变化通知
		// pRequest					消息对象
		// dwStatus					HTTP新状态
		virtual void OnHttpStatusChanged(HttpRequest* pRequest,DWORD dwStatus);

		//	HTTP请求完成
		// pRequest					消息对象
		// bSuccessed				HTTP请求是否发生错误，超时
		virtual void OnHttpFinished(HttpRequest* pRequest,BOOL bSuccessed);

		// 进度通知
		// pRequest					消息对象
		// fFinishedPercent		进度完成百分比
		// dwReceivedSize		已接收大小
		// dwTotalSize				总大小
		virtual void OnHttpProgress(
			HttpRequest* pRequest,
			double fFinishedPercent,
			DWORD dwReceivedSize,
			DWORD dwTotalSize
			);
	};
}

