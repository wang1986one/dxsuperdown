#include "stdafx.h"
#include "MainWnd.h"

CMainWnd::CMainWnd(void)
{
}

CMainWnd::~CMainWnd(void)
{
	PostQuitMessage(0);
}

void CMainWnd::InitWindow()
{
	// 成员初始化
	
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
	CString strControlName=msg.pSender->GetName();
	if (msg.sType==_T("click"))
	{ 
		return;
	}
}

LRESULT CMainWnd::HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
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
	return _T("DxSuperdown.dll");	// Bin/skin目录下所有文件使用zip打包后重命名得来
}

