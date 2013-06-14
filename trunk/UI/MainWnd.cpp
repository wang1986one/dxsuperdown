#include "stdafx.h"
#include "MainWnd.h"

#ifdef _DEBUG
#include <Utils\MemLeak.h>
#define new DEBUG_NEW
#endif

CMainWnd::CMainWnd(void)
{
}

CMainWnd::~CMainWnd(void)
{
	PostQuitMessage(0);
}

void CMainWnd::InitWindow()
{
	// ��Ա��ʼ��
	SidebarLayout	= static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("SidebarLayout")));
	m_btnClose		= static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("closebtn")));
	m_btnMin			= static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("minbtn")));
	m_btnMax		= static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("maxbtn")));
	m_btnRestore	= static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("restorebtn")));
}

void CMainWnd::OnFinalMessage(HWND hWnd)
{
	__super::OnFinalMessage(hWnd);
	delete this; 
}

CDuiString CMainWnd::GetSkinFolder()
{
#ifdef _DEBUG
	return _T("Skin\\");
#else
	return _T("");
#endif // _DEBUG
}

CDuiString CMainWnd::GetSkinFile()
{
	return _T("MainWnd.xml");
}

void CMainWnd::Notify( TNotifyUI &msg )
{
	CDuiString strControlName=msg.pSender->GetName();
	if (msg.sType==_T("click"))
	{
		if ( msg.pSender == m_btnClose)
		{
			Close();
			return;
		}
		else if (msg.pSender == m_btnMin)
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE , 0);
			return;
		}
		else if ( msg.pSender == m_btnMax)
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE | HTCAPTION , 0);
			return;
		}
		else if ( msg.pSender == m_btnRestore)
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE | HTCAPTION , 0);
			return;
		}
		else	// ��ȫ�ֿ��ư�ť�������Ķ��Ĺ��ܰ�ť���ƴ���ַ�����������
			OnClick(msg);
		return;
	}
	else if(msg.sType==_T("selectchanged"))
	{
		OnSelectChaged(msg);
		return;
	}
}

LRESULT CMainWnd::HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	if (uMsg==WM_MENU_NOTIFY)
	{
		OnMenu(wParam,lParam);
		return S_OK;
	}
	bHandled = FALSE;
	return FALSE;
}

UINT CMainWnd::GetClassStyle() const
{
	return CS_DROPSHADOW | WindowImplBase::GetClassStyle();
}

DuiLib::UILIB_RESOURCETYPE CMainWnd::GetResourceType() const
{
#ifdef _DEBUG
	return UILIB_FILE;
#else
	return UILIB_ZIP;
#endif // _DEBUG
}

DuiLib::CDuiString CMainWnd::GetZIPFileName() const
{
	return _T("DxSuperdown.dll");	// Bin/skinĿ¼�������ļ�ʹ��zip���������������
}

void CMainWnd::OnClick( TNotifyUI &msg )
{
	CDuiString strControlName=msg.pSender->GetName();
	if (strControlName.CompareNoCase(_T("btn_menu")) == 0)	
	{
		//CMenuWnd* pMenu = new CMenuWnd(m_hWnd);
		//CPoint point = msg.ptMouse;
		////POINT point ={ GET_X_LPARAM(msg.lParam), GET_Y_LPARAM(msg.lParam) };
		//CControlUI * pControl = this->m_PaintManager.FindControl(point);
		////CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(point));
		//::ClientToScreen(m_hWnd, &point);
		//STRINGorID xml(IDR_XML_MENU);
		//pMenu->Init(NULL, xml, _T("xml"), point, pControl);
		////����������ؼ�����ҳ
		//CActiveXUI* pActiveXUI = static_cast<CActiveXUI*>(m_PaintManager.FindControl(_T("���԰�IE")));
		//if( pActiveXUI ) 
		//{
		//	IWebBrowser2* pWebBrowser = NULL;
		//	pActiveXUI->GetControl(IID_IWebBrowser2, (void**)&pWebBrowser);
		//	if( pWebBrowser != NULL ) 
		//	{
		//		pWebBrowser->Navigate(L"http://www.google.com",NULL,NULL,NULL,NULL);  
		//		//pWebBrowser->Navigate(L"about:blank",NULL,NULL,NULL,NULL); 
		//		pWebBrowser->Release();
		//	}
		//}
	}
}

void CMainWnd::OnSelectChaged( TNotifyUI &msg )
{
	CDuiString name = msg.pSender->GetName();
	if (name==_T("ToggleSidebar"))
	{
		//CVerticalLayoutUI * pControl = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(_T("SidebarLayout")));
		SidebarLayout->SetVisible(!SidebarLayout->IsVisible());
	}
	else if(name==_T("Download")
		||name==_T("VideoMerger")
		||name==_T("MessageBoard")
		||name==_T("Play")
		||name==_T("DemoSite")
		||name==_T("TEST1")
		||name==_T("TEST2")
		||name==_T("TEST3"))
	{
			CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("����ǩҳ")));
			if(name==_T("Download"))
				pControl->SelectItem(0);
			else if(name==_T("VideoMerger"))
				pControl->SelectItem(1);
			else if(name==_T("Play"))
				pControl->SelectItem(2);
			else if(name==_T("MessageBoard"))
				pControl->SelectItem(3);
			else if(name==_T("DemoSite"))
				pControl->SelectItem(4);
			else if(name==_T("TEST1"))
				pControl->SelectItem(5);
			else if(name==_T("TEST2"))
				pControl->SelectItem(6);
			else if(name==_T("TEST3"))
				pControl->SelectItem(7);
	}
	
	else if(name==_T("AllTasks")
		||name==_T("IsDown")
		||name==_T("Complete")
		||name==_T("Recycle"))
	{
		CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("���ر�ǩҳ")));
		if(name==_T("AllTasks"))
			pControl->SelectItem(0);
		else if(name==_T("IsDown"))
			pControl->SelectItem(1);
		else if(name==_T("Complete"))
			pControl->SelectItem(2);
		else if(name==_T("Recycle"))
			pControl->SelectItem(3);

	}

}

void CMainWnd::OnMenu( WPARAM wParam,LPARAM lParam )
{
	CControlUI * pControl = NULL;
	CDuiString strMenuName = (TCHAR *)(LPCTSTR)pControl->GetUserData();
	if (strMenuName == _T("Menu_Clear"))
		Close();
	else if (
		strMenuName == _T("Menu_ZoomRatio_400")
		|| strMenuName == _T("Menu_ZoomRatio_200")
		|| strMenuName == _T("Menu_ZoomRatio_150")
		|| strMenuName == _T("Menu_ZoomRatio_125")
		|| strMenuName == _T("Menu_ZoomRatio_100")
		|| strMenuName == _T("Menu_ZoomRatio_75")
		|| strMenuName == _T("Menu_ZoomRatio_50"))
	{
		 //OnMenu_ZoomRatio(msg);
	}
}

LRESULT CMainWnd::OnSysCommand( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	switch ( wParam & 0xFFF0)
	{	// �������Ͻǿ��ư�ť
	case SC_RESTORE:
		m_btnMax->SetVisible(true);
		m_btnRestore->SetVisible(false);
		break;
	case SC_MAXIMIZE:
		m_btnMax->SetVisible(false);
		m_btnRestore->SetVisible(true);
		break;
	case SC_CLOSE:
		Close();
		break;
	}

	return WindowImplBase::OnSysCommand(uMsg,wParam,lParam,bHandled);
}

