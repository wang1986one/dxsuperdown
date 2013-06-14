#pragma once

#include "DuiLib/Utils/WinImplBase.h"

class CMainWnd
	: public WindowImplBase
{
public:
	CMainWnd(void);
	~CMainWnd(void);

	enum _enContentPage
	{
		Content_Download=0,
		Content_VideoMerger,
		Content_Play,
		Content_MessageBoard,
		Content_DemoSite,
		Content_TEST1,
		Content_TEST2,
		Content_TEST3,
	};

	enum _enDownloadPage
	{
		Download_AllTasks=0,
		Download_IsDown,
		Download_Complete,
		Download_Recycle,
	};

private:
	virtual void InitWindow();
	virtual void OnFinalMessage(HWND hWnd);
	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual void Notify( TNotifyUI &msg );
	virtual LRESULT HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual UINT GetClassStyle() const;
	virtual UILIB_RESOURCETYPE GetResourceType() const;
	virtual CDuiString GetZIPFileName() const;
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void OnClick(TNotifyUI &msg);
	void OnSelectChaged(TNotifyUI &msg);
	void OnMenu(WPARAM wParam,LPARAM lParam);
private:
	// 成员指针
	CTabLayoutUI*			m_TabContent;			// 功能区Tab
	CTabLayoutUI*			m_TabDownload;		// 下载列表Tab
	CVerticalLayoutUI * SidebarLayout;

	// 窗口控制按钮
	CButtonUI* m_btnClose;
	CButtonUI* m_btnMin;
	CButtonUI* m_btnMax;
	CButtonUI* m_btnRestore;
};
