#include "stdafx.h"
#include "UI/MainWnd.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	CPaintManagerUI::SetInstance(hInstance);

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) )
		return 0;
 
	CMainWnd* pFrame = new CMainWnd();//主窗体类
	if(pFrame==NULL)
		return 0;
	pFrame->CreateDuiWindow(NULL,_T("DxSuperdown"),UI_WNDSTYLE_DIALOG | WS_MAXIMIZEBOX | WS_MINIMIZEBOX);
	pFrame->CenterWindow();
	pFrame->SetIcon(101);
	pFrame->ShowWindow();

	CPaintManagerUI::MessageLoop();	// 启动UI主消息循环
 
	::CoUninitialize();
	return 0;
}