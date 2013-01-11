#pragma once

#include "DuiLib/Utils/WinImplBase.hpp"

class CMainWnd
	: public WindowImplBase
{
public:
	CMainWnd(void);
	~CMainWnd(void);

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

private:
	// ≥…‘±÷∏’Î
};
