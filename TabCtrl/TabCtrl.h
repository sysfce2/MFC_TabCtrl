//==========================================================
// Author: Baradzenka Aleh (baradzenka@gmail.com)
//==========================================================
// 
#pragma once
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#pragma warning(push)
#pragma warning(disable : 4458)   // declaration of 'nativeCap' hides class member.
#include <gdiplus.h>
#pragma warning(pop)
// 
#if (!defined(_MSC_VER) && __cplusplus < 201103L) || (defined(_MSC_VER) && _MSC_VER < 1900)   // C++11 is not supported.
	#define override
#endif
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
class TabCtrl : public CWnd
{	DECLARE_DYNCREATE(TabCtrl)

///////////////////////////////////////
// PUBLIC
///////////////////////////////////////
public:
	struct Draw
	{	virtual bool IsDrawTabsStraightOrder(TabCtrl const * /*ctrl*/) { return true; }   // true - paint tabs left to right, false - reverse order.
		virtual void DrawBegin(TabCtrl const * /*ctrl*/, CDC * /*dc*/) {}
		virtual void DrawBorder(TabCtrl const * /*ctrl*/, CDC * /*dc*/, CRect const * /*rect*/) {}
		virtual void DrawControlAreaBack(TabCtrl const * /*ctrl*/, CDC * /*dc*/, CRect const * /*rect*/) {}
		virtual void DrawTab(TabCtrl const * /*ctrl*/, CDC * /*dc*/, HANDLE /*tab*/, CRgn * /*rgn*/) {}
		virtual void DrawButtonClose(TabCtrl const * /*ctrl*/, CDC * /*dc*/, CRect const * /*rect*/, bool /*hover*/, bool /*pushed*/) {}
		virtual void DrawButtonMenu(TabCtrl const * /*ctrl*/, CDC * /*dc*/, CRect const * /*rect*/, bool /*hover*/, bool /*pushed*/, bool /*partialView*/) {}
		virtual void DrawButtonScrollLeft(TabCtrl const * /*ctrl*/, CDC * /*dc*/, CRect const * /*rect*/, bool /*hover*/, bool /*pushed*/, bool /*partialView*/) {}
		virtual void DrawButtonScrollRight(TabCtrl const * /*ctrl*/, CDC * /*dc*/, CRect const * /*rect*/, bool /*hover*/, bool /*pushed*/, bool /*partialView*/) {}
		virtual void DrawWindowsAreaBack(TabCtrl const * /*ctrl*/, CDC * /*dc*/, CRect const * /*rect*/) {}
		virtual void DrawEnd(TabCtrl const * /*ctrl*/, CDC * /*dc*/) {}
	};
	interface IRecalc
	{	virtual int GetBorderWidth(TabCtrl const *ctrl, IRecalc *base) = 0;
			// 
		virtual CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) = 0;
		virtual CRect GetWindowsAreaPadding(TabCtrl const *ctrl, IRecalc *base) = 0;
			// 
		virtual CRect GetTabHorzMargin(TabCtrl const *ctrl, IRecalc *base) = 0;   // uses only CRect::left and CRect::right.
		virtual CRect GetTabPadding(TabCtrl const *ctrl, IRecalc *base) = 0;
		virtual int GetTabImageTextSpace(TabCtrl const *ctrl, IRecalc *base) = 0;   // space between picture and text.
		virtual int GetTabExtraWidth(TabCtrl const *ctrl, IRecalc *base, HANDLE tab) = 0;   // additional width of tab.
		virtual int GetTabMinWidth(TabCtrl const *ctrl, IRecalc *base) = 0;   // minimal width of tab.
			// 
		virtual CRect GetButtonCloseHorzMargin(TabCtrl const *ctrl, IRecalc *base) = 0;   // uses only CRect::left and CRect::right.
		virtual CRect GetButtonMenuHorzMargin(TabCtrl const *ctrl, IRecalc *base) = 0;   // uses only CRect::left and CRect::right.
		virtual CRect GetButtonScrollLeftHorzMargin(TabCtrl const *ctrl, IRecalc *base) = 0;   // uses only CRect::left and CRect::right.
		virtual CRect GetButtonScrollRightHorzMargin(TabCtrl const *ctrl, IRecalc *base) = 0;   // uses only CRect::left and CRect::right.
	};
	interface IBehavior
	{	virtual HANDLE HitTest(TabCtrl const *ctrl, IBehavior *base, CPoint point) = 0;   // get tab in the given point.
		virtual bool SetCursor(TabCtrl const *ctrl, IBehavior *base) = 0;   // return true if you set cursor.
	};
	struct ToolTip
	{	virtual CToolTipCtrl *CreateToolTip(TabCtrl * /*ctrl*/) { return NULL; }
		virtual void DestroyToolTip(CToolTipCtrl * /*tooltip*/) {}
	};
	struct Ability
	{	virtual bool CanShowButtonClose(TabCtrl const * /*ctrl*/) { return true; }
		virtual bool CanShowButtonMenu(TabCtrl const * /*ctrl*/) { return true; }
		virtual bool CanShowButtonScroll(TabCtrl const * /*ctrl*/) { return true; }   // left scroll and right scroll.
	};
	struct Notify
	{	virtual void OnTabPreCreate(TabCtrl const * /*ctrl*/, HWND /*wnd*/, TCHAR const * /*text*/, int /*image*/) {}
		virtual void OnTabPostCreate(TabCtrl * /*ctrl*/, HANDLE /*tab*/) {}
		virtual void OnTabPreDestroy(TabCtrl const * /*ctrl*/, HANDLE /*tab*/) {}
			// 
		virtual void OnCloseButtonClicked(TabCtrl * /*ctrl*/, CRect const * /*rect*/, CPoint /*ptScr*/) {}   // ptScr - in screen space.
		virtual void OnMenuButtonClicked(TabCtrl * /*ctrl*/, CRect const * /*rect*/, CPoint /*ptScr*/) {}   // ptScr - in screen space.
		virtual void OnTabSelected(TabCtrl * /*ctrl*/, HANDLE /*tab*/) {}
		virtual void OnLButtonDown(TabCtrl const * /*ctrl*/, HANDLE /*tab*/, CPoint /*ptScr*/) {}   // ptScr - in screen space.
		virtual void OnLButtonDblClk(TabCtrl * /*ctrl*/, HANDLE /*tab*/, CPoint /*ptScr*/) {}   // ptScr - in screen space.
		virtual void OnRButtonDown(TabCtrl * /*ctrl*/, HANDLE /*tab*/, CPoint /*ptScr*/) {}		// ptScr - in screen space, tab can be NULL.
		virtual void OnRButtonUp(TabCtrl * /*ctrl*/, HANDLE /*tab*/, CPoint /*ptScr*/) {}   // ptScr - in screen space, tab can be NULL.
			// 
		virtual void OnStartDrag(TabCtrl const * /*ctrl*/, HANDLE /*tab*/, CPoint /*ptScr*/) {}   // ptScr - in screen space.
		virtual void OnDrag(TabCtrl * /*ctrl*/, HANDLE /*tab*/, CPoint /*ptScr*/, bool /*outside*/) {}   // ptScr - in screen space, outside==true - dragging out of tabs area.
		virtual void OnFinishDrag(TabCtrl const * /*ctrl*/, HANDLE /*tab*/, bool /*cancel*/) {}   // cancel==false - dragging was finished using left button up.
	}; 

public:
	TabCtrl();
	~TabCtrl();

public:
	bool Create(CWnd *parent, DWORD style, RECT const &rect, UINT id);
	HANDLE AddTab(HWND wnd, TCHAR const *text, int image);   // 'image'=-1 for tab without image.
	HANDLE InsertTab(HANDLE before, HWND wnd, TCHAR const *text, int image);   // 'image'=-1 for tab without image.
	void RemoveTabBefore(HANDLE before, HANDLE src);
	void RemoveTabAfter(HANDLE after, HANDLE src);
	void DeleteTab(HANDLE tab);
	void DeleteAllTabs();
		// 
	void Update(bool redraw = true);   // recalculate and redraw control.
		// 
	void SetDrawManager(Draw *p/*or null*/);
	Draw *GetDrawManager() const;
	void SetRecalcManager(IRecalc *p/*or null*/);   // or NULL for default manager.
	IRecalc *GetRecalcManager() const;
	void SetBehaviorManager(IBehavior *p/*or null*/);   // or NULL for default manager.
	IBehavior *GetBehaviorManager() const;
	void SetToolTipManager(ToolTip *p/*or null*/);
	ToolTip *GetToolTipManager() const;
	void SetAbilityManager(Ability *p/*or null*/);   // or NULL for default manager.
	Ability *GetAbilityManager() const;
	void SetNotifyManager(Notify *p/*or null*/);
	Notify *GetNotifyManager() const;
		// 
	enum Layout { LayoutTop, LayoutBottom };
	void SetLayout(Layout layout);
	Layout GetLayout() const;
		// 
	enum Behavior { BehaviorScale, BehaviorScroll };
	void SetBehavior(Behavior behavior);
	Behavior GetBehavior() const;
		// 
	enum SysImage	// order of images of system buttons (close, menu, left scroll, right scroll).
	{	SysImageButtonClose,
		SysImageButtonMenuFullView, SysImageButtonMenuPartialView,
		SysImageButtonScrollLeftAllow, SysImageButtonScrollLeftForbid,
		SysImageButtonScrollRightAllow, SysImageButtonScrollRightForbid
	};
	bool CreateSystemImage(HMODULE moduleRes/*or null*/, UINT resID/*or 0*/, bool pngImage, int imageWidth, COLORREF clrTransp=CLR_NONE);   // system images must have the same order as SysImage enum.
	Gdiplus::Bitmap *GetSystemImage() const;
	bool GetSystemImageList(COLORREF clrDstBack/*or CLR_NONE*/, CImageList *imageList/*out*/) const;
	CSize GetSystemImageSize() const;
	COLORREF GetSystemImageTranspColor() const;
		// 
	bool CreateImage(HMODULE moduleRes/*or null*/, UINT resNormalID/*or 0*/, UINT resDisableID/*or 0*/, bool pngImage, int imageWidth, COLORREF clrTransp=CLR_NONE);
	void GetImage(Gdiplus::Bitmap **normal/*out,or null*/, Gdiplus::Bitmap **disable/*out,or null*/) const;
	bool GetImageList(COLORREF clrDstBack/*or CLR_NONE*/, CImageList *normal/*out,or null*/, CImageList *disable/*out,or null*/) const;
	void GetImageSize(CSize *szNormal/*out,or null*/, CSize *szDisable/*out,or null*/) const;
	COLORREF GetImageTranspColor() const;
		// 
	bool SetCursor(UINT resID);
	bool SetCursor(HMODULE module/*or null*/, UINT resID);
	bool SetCursor(HCURSOR cursor);
	HCURSOR GetCursor() const;
		// 
	bool SetFontNormal(CFont *font);
	bool SetFontNormal(LOGFONT const *lf);
	CFont *GetFontNormal();
		// 
	bool SetFontSelect(CFont *font);
	bool SetFontSelect(LOGFONT const *lf);
	CFont *GetFontSelect();
		// 
	void SetTabTooltipText(HANDLE tab, TCHAR const *text);   // the tooltip that is always displayed for a tab, regardless of whether its text is fully visible or not.
	CString GetTabTooltipText(HANDLE tab) const;
	void SetButtonCloseToolTipText(TCHAR const *text);
	CString GetButtonCloseToolTipText() const;
	void SetButtonMenuToolTipText(TCHAR const *text);
	CString GetButtonMenuToolTipText() const;
	void SetButtonScrollLeftToolTipText(TCHAR const *text);
	CString GetButtonScrollLeftToolTipText() const;
	void SetButtonScrollRightToolTipText(TCHAR const *text);
	CString GetButtonScrollRightToolTipText() const;
		// 
	void SetTabText(HANDLE tab, TCHAR const *text);
	CString GetTabText(HANDLE tab) const;
	void SetTabImage(HANDLE tab, int image);   // 'image'=-1 for tab without image.
	int GetTabImage(HANDLE tab) const;
	void SetTabWindow(HANDLE tab, HWND wnd);
	HWND GetTabWindow(HANDLE tab) const;
	void SetTabData(HANDLE tab, __int64 data);   // set any user data for the tab.
	__int64 GetTabData(HANDLE tab) const;
		// 
	void CopyTabContent(HANDLE dst, TabCtrl const *tabCtrlSrc, HANDLE src);   // copy: text, image, data, tooltip text and enable/disable state.
		// 
	int GetNumberTabs() const;   // get number of tabs in the control.
	HANDLE GetFirstEnableTab() const;
	HANDLE GetPrevEnableTab(HANDLE tab) const;
	HANDLE GetNextEnableTab(HANDLE tab) const;
		// 
	void SelectTab(HANDLE tab);   // select tab.
	HANDLE GetSelectedTab() const;   // get handle of current active tab (whose child window is visible).
	HANDLE GetTabUnderCursor() const;   // get tab under cursor.
	HANDLE GetPushedTab() const;   // get handle of pushed tab.
		// 
	void DisableTab(HANDLE tab, bool disable);   // disable/enable tab.
	bool IsTabDisabled(HANDLE tab) const;
		// 
	HANDLE HitTest(CPoint point) const;   // get tab in the given point or NULL, 'point' - in screen space.
	HANDLE GetTabHandleByIndex(int idx) const;   // idx - index of tab (>=0).
	int GetTabIndexByHandle(HANDLE tab) const;   // get index of tab (return value is >=0).
	bool IsTabExist(HANDLE tab) const;   // return true - tab with this handle exists in the control.
	HANDLE GetTabWithWindowID(int id) const;   // get tab whose window has id.
	int CompareTabsPosition(HANDLE tab1, HANDLE tab2) const;   // return <0 - index of tab1 less than tab2, 0 - indexes are equal.
		// 
	RECT GetTabRect(HANDLE tab) const;
	bool IsTabVisible(HANDLE tab, bool *partially/*out, or null*/) const;   // tab can be moved off the left or right edge of the control in BehaviorScroll mode.
	void EnsureTabVisible(HANDLE tab);   // shift tab in a visible area (use for the BehaviorScroll mode).
		// 
	void ScrollTabsToBegin();   // shift to show first (left) tab (use for the BehaviorScroll mode).
	void ScrollTabsToEnd();   // shift to show last (right) tab (use for the BehaviorScroll mode).
	void SetTabsScrollingStep(int step);   // width of one step for scrolling (in pixels >=1) (use for the BehaviorScroll mode).
	int GetTabsScrollingStep() const;
		// 
	void ShowBorder(bool show);   // border is visible if IsBorderVisible()==true and IRecalc::GetBorderWidth(...) returns >0.
	bool IsBorderVisible() const;
	void EqualTabsSize(bool equal);   // true - the same width for all tabs.
	bool IsEqualTabsSize() const;
	void EnableTabRemove(bool enable);   // true - you can change positions of tabs using mouse.
	bool IsTabRemoveEnable() const;
	void HideSingleTab(bool hide);   // true - hide control area if control has only one tab. 
	bool IsHideSingleTab() const;
		// 
	void ShowButtonClose(bool show);
	bool IsButtonCloseVisible() const;
	void ShowButtonMenu(bool show);
	bool IsButtonMenuVisible() const;
	void ShowButtonsScroll(bool show);   // for left scroll and right scroll at the same time.
	bool IsButtonsScrollVisible() const;
		// 
	void WatchCtrlActivity(bool watch);   // true - control saves activity state which you can get using IsActive().
	bool IsWatchCtrlActivity() const;
		// 
	bool IsTabDragging() const;   // return true - user is removing a tab.
	void CancelTabDragging();
		// 
	bool IsActive() const;   // return true - one of child windows is active (has focus), works only if IsWatchActivityCtrl()==true.
		// 
	RECT GetCtrlArea() const;   // control area includes tabs area and control (system) buttons.
	RECT GetTabsArea() const;
	RECT GetWindowsArea() const;   // returns area for child windows.
		// 
	int CalcCtrlAreaHeight();   // return necessary height of control area.
		// 
	RECT GetButtonCloseRect() const;
	RECT GetButtonMenuRect() const;
	RECT GetButtonScrollLeftRect() const;
	RECT GetButtonScrollRightRect() const;
		// 
	bool LoadState(CWinApp *app, TCHAR const *section, TCHAR const *entry);   // load state from registry.
	bool SaveState(CWinApp *app, TCHAR const *section, TCHAR const *entry) const;   // save state in registry.
	bool LoadState(CArchive *ar);
	bool SaveState(CArchive *ar) const;

public:	// functions of IRecalc interface, return information from current recalc manager.
	int GetBorderWidth() const;
		// 
	CRect GetControlAreaPadding() const;
	CRect GetWindowsAreaPadding() const;
		// 
	CRect GetTabHorzMargin() const;
	CRect GetTabPadding() const;
	int GetTabImageTextSpace() const;   // space between picture and text.
	int GetTabExtraWidth(HANDLE tab) const;
	int GetTabMinWidth() const;
		// 
	CRect GetButtonCloseHorzMargin() const;
	CRect GetButtonMenuHorzMargin() const;
	CRect GetButtonScrollLeftHorzMargin() const;
	CRect GetButtonScrollRightHorzMargin() const;

public:
	CToolTipCtrl *GetToolTip() const;   // get used tooltip object (NULL if tooltip wasn't created).

///////////////////////////////////////
// PRIVATE
///////////////////////////////////////
private:
	struct Private;
	Private &p;

///////////////////////////////////////
// PROTECTED
///////////////////////////////////////
protected:
	DECLARE_MESSAGE_MAP()
	BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD style, const RECT& rect, CWnd *parentWnd, UINT id, CCreateContext *context = NULL) override;
	afx_msg void OnDestroy();
	BOOL PreTranslateMessage(MSG *msg) override;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	LRESULT OnMouseLeave(WPARAM wp, LPARAM lp);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd *pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlRecalcStub : TabCtrl::IRecalc
{	int GetBorderWidth(TabCtrl const *ctrl, IRecalc *base) override { return base->GetBorderWidth(ctrl,NULL); }
		// 
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override { return base->GetControlAreaPadding(ctrl,NULL); }
	CRect GetWindowsAreaPadding(TabCtrl const *ctrl, IRecalc *base) override { return base->GetWindowsAreaPadding(ctrl,NULL); }
		// 
	CRect GetTabHorzMargin(TabCtrl const *ctrl, IRecalc *base) override { return base->GetTabHorzMargin(ctrl,NULL); }
	CRect GetTabPadding(TabCtrl const *ctrl, IRecalc *base) override { return base->GetTabPadding(ctrl,NULL); }
	int GetTabImageTextSpace(TabCtrl const *ctrl, IRecalc *base) override { return base->GetTabImageTextSpace(ctrl,NULL); }   // space between picture and text .
	int GetTabExtraWidth(TabCtrl const *ctrl, IRecalc *base, HANDLE tab) override { return base->GetTabExtraWidth(ctrl,NULL,tab); }
	int GetTabMinWidth(TabCtrl const *ctrl, IRecalc *base) override { return base->GetTabMinWidth(ctrl,NULL); }
		// 
	CRect GetButtonCloseHorzMargin(TabCtrl const *ctrl, IRecalc *base) override { return base->GetButtonCloseHorzMargin(ctrl,NULL); }
	CRect GetButtonMenuHorzMargin(TabCtrl const *ctrl, IRecalc *base) override { return base->GetButtonMenuHorzMargin(ctrl,NULL); }
	CRect GetButtonScrollLeftHorzMargin(TabCtrl const *ctrl, IRecalc *base) override { return base->GetButtonScrollLeftHorzMargin(ctrl,NULL); }
	CRect GetButtonScrollRightHorzMargin(TabCtrl const *ctrl, IRecalc *base) override { return base->GetButtonScrollRightHorzMargin(ctrl,NULL); }
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlBehaviorStub : TabCtrl::IBehavior
{	HANDLE HitTest(TabCtrl const *ctrl, IBehavior *base, CPoint point) override { return base->HitTest(ctrl,NULL,point); }   // get tab in the given point.
	bool SetCursor(TabCtrl const *ctrl, IBehavior *base) override { return base->SetCursor(ctrl,NULL); }
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
struct TabCtrlStyle_base : 
	TabCtrl::Draw, 
	TabCtrlRecalcStub,
	TabCtrlBehaviorStub,
	TabCtrl::ToolTip
{
	void Install(TabCtrl *ctrl);

		// TabCtrl::Draw.
	void DrawBorder(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
	void DrawControlAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
	void DrawTab(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRgn *rgn) override;
	void DrawButtonClose(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
	void DrawButtonMenu(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed, bool partialView) override;
	void DrawButtonScrollLeft(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed, bool partialView) override;
	void DrawButtonScrollRight(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed, bool partialView) override;
	void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;

		// TabCtrl::ToolTip.
	CToolTipCtrl *CreateToolTip(TabCtrl *ctrl) override;
	void DestroyToolTip(CToolTipCtrl *tooltip) override;

	virtual COLORREF GetBorderColor(TabCtrl const *ctrl);
	virtual COLORREF GetTabBorderColor(TabCtrl const *ctrl);
	virtual COLORREF GetCtrlAreaBackColor(TabCtrl const *ctrl);
	virtual COLORREF GetWndsAreaBackColor(TabCtrl const *ctrl);
	virtual COLORREF GetTabSelectedBackColor(TabCtrl const *ctrl);
	virtual COLORREF GetTabTextColor(TabCtrl const *ctrl, HANDLE tab);
	virtual COLORREF GetButtonCloseColor(TabCtrl const *ctrl, bool hover, bool pushed);
	virtual COLORREF GetButtonMenuColor(TabCtrl const *ctrl, bool hover, bool pushed);
	virtual COLORREF GetButtonScrollLeftColor(TabCtrl const *ctrl, bool hover, bool pushed);
	virtual COLORREF GetButtonScrollRightColor(TabCtrl const *ctrl, bool hover, bool pushed);
	virtual COLORREF GetChildWndBackColor(TabCtrl const *ctrl);
	virtual COLORREF GetEmptyWndsAreaBackColor(TabCtrl const *ctrl);

	virtual void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn);   // draw background of tab.
	virtual void DrawTabContext(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn);   // draw image and text.
	virtual void DrawTabImage(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn);
	virtual void DrawTabText(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn);
	virtual void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed);   // draw close, menu or scroll button without image.

	void DrawMarker(TabCtrl const *ctrl, CDC *dc, Gdiplus::Bitmap *bmp, CRect const *rcDst, int image, COLORREF clrTransp/*or CLR_NONE*/, COLORREF clrFill);
	void DrawImage(TabCtrl const *ctrl, CDC *dc, Gdiplus::Bitmap *bmp, CPoint const &ptDst, int image, CSize const &szSrc, COLORREF clrTransp/*or CLR_NONE*/);
	enum Side { SideTop, SideBottom };
	void DrawHalfRoundFrame(CDC *pDC, CRect const *rect, Side side, int radius, COLORREF clrBorder, COLORREF clrBack);
	void DrawFrame(CDC *pDC, POINT const *pPoints, int iCount, COLORREF clrBorder, COLORREF clrBack);
	void DrawFrame(CDC *pDC, POINT const *pPoints, int iCount, COLORREF clrLine);
	void DrawGradient(CDC *pDC, CRect const *rect, bool horz, COLORREF clrTopLeft, COLORREF clrBottomRight);
	void DrawLine(CDC *pDC, int x1, int y1, int x2, int y2, COLORREF clrLine);
	void DrawLine(CDC *pDC, int x1, int y1, int x2, int y2);
	void DrawRect(CDC *pDC, int x1, int y1, int x2, int y2, COLORREF clrLine);
	void DrawRect(CDC *pDC, CRect const *rect, COLORREF clrLine);
	void DrawRect(CDC *pDC, CRect const *rect);
	COLORREF PixelAlpha(COLORREF src, COLORREF dst, int percent);
	void FillSolidRect(CDC *dc, CRect const *rc, COLORREF color);
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Visual Studio 2003
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2003_base : TabCtrlStyle_base
{		// TabCtrl::Draw.
	void DrawButtonClose(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
	void DrawButtonMenu(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed, bool partialView) override;
	void DrawButtonScrollLeft(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed, bool partialView) override;
	void DrawButtonScrollRight(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed, bool partialView) override;

	COLORREF GetCtrlAreaBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabTextColor(TabCtrl const *ctrl, HANDLE tab) override;
	COLORREF GetButtonCloseColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	COLORREF GetButtonMenuColor(TabCtrl const *ctrl, bool hover, bool pushed) override;

	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2003_client : TabCtrlStyle_VS2003_base
{		// TabCtrl::IRecalc.
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetWindowsAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetTabPadding(TabCtrl const *ctrl, IRecalc *base) override;

		// TabCtrl::Draw.
	void DrawControlAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
	void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;

		// TabCtrlStyle_base.
	void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	COLORREF GetTabBorderColor(TabCtrl const *ctrl) override;
};
// 
struct TabCtrlStyle_VS2003_client_custom1 : TabCtrlStyle_VS2003_client
{		// TabCtrl::Draw.
	void DrawButtonClose(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
	void DrawButtonMenu(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed, bool partialView) override;
	void DrawButtonScrollLeft(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed, bool partialView) override;
	void DrawButtonScrollRight(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed, bool partialView) override;

	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2003_bars : TabCtrlStyle_VS2003_base
{		// TabCtrl::IRecalc.
	int GetBorderWidth(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetTabPadding(TabCtrl const *ctrl, IRecalc *base) override;

		// TabCtrl::Draw.
	void DrawControlAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;

		// TabCtrlStyle_base.
	void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	COLORREF GetTabBorderColor(TabCtrl const *ctrl) override;
};
// 
struct TabCtrlStyle_VS2003_bars_custom1 : TabCtrlStyle_VS2003_bars
{		// TabCtrl::IRecalc.
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetWindowsAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;

		// TabCtrl::Draw.
	void DrawControlAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
	void DrawButtonClose(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
	void DrawButtonMenu(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed, bool partialView) override;
	void DrawButtonScrollLeft(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed, bool partialView) override;
	void DrawButtonScrollRight(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed, bool partialView) override;
	void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;

	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
	COLORREF GetTabBorderColor(TabCtrl const *ctrl) override;
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Visual Studio 2008
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2008_client_base : TabCtrlStyle_base
{		// TabCtrl::IRecalc.
	int GetBorderWidth(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetWindowsAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetTabPadding(TabCtrl const *ctrl, IRecalc *base) override;
	int GetTabExtraWidth(TabCtrl const *ctrl, IRecalc *base, HANDLE tab) override;
	int GetTabMinWidth(TabCtrl const *ctrl, IRecalc *base) override;

		// TabCtrl::IBehavior.
	HANDLE HitTest(TabCtrl const *ctrl, IBehavior *base, CPoint point) override;   // get tab in the given point.

		// TabCtrl::Draw.
	bool IsDrawTabsStraightOrder(TabCtrl const * /*ctrl*/) override { return false; }
	void DrawControlAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
	void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;

		// TabCtrlStyle_base.
	void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	void DrawTabContext(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;   // draw image and text.

	virtual COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool active, bool disable) = 0;
	virtual COLORREF GetTabOutlineColor(TabCtrl const *ctrl, bool active, bool hover, bool disable, bool left) = 0;
	virtual COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool active, bool hover, bool disable) = 0;
	virtual COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool active, bool hover, bool disable) = 0;

	void GetTabOutline(TabCtrl const *ctrl, HANDLE tab, CRect const *rect, bool top, POINT pts[8]/*out*/, RECT *rcFill/*out*/) const;
	bool HitTest(TabCtrl const *ctrl, HANDLE tab, bool top, CPoint point) const;
	int GetSlantWidth(TabCtrl const *ctrl) const;
	void DrawBeveledRect(CDC *pDC, CRect const *rect, int bevel);
};
// 
struct TabCtrlStyle_VS2008_client_classic : TabCtrlStyle_VS2008_client_base
{		// TabCtrlStyle_VS2008_client_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool active, bool disable) override;
	COLORREF GetTabOutlineColor(TabCtrl const *ctrl, bool active, bool hover, bool disable, bool left) override;
	COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool active, bool hover, bool disable) override;
	COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool active, bool hover, bool disable) override;
};
// 
struct TabCtrlStyle_VS2008_client_blue : TabCtrlStyle_VS2008_client_base
{		// TabCtrlStyle_VS2008_client_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool active, bool disable) override;
	COLORREF GetTabOutlineColor(TabCtrl const *ctrl, bool active, bool hover, bool disable, bool left) override;
	COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool active, bool hover, bool disable) override;
	COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool active, bool hover, bool disable) override;
};
// 
struct TabCtrlStyle_VS2008_client_silver : TabCtrlStyle_VS2008_client_base
{		// TabCtrlStyle_VS2008_client_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool active, bool disable) override;
	COLORREF GetTabOutlineColor(TabCtrl const *ctrl, bool active, bool hover, bool disable, bool left) override;
	COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool active, bool hover, bool disable) override;
	COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool active, bool hover, bool disable) override;

		// TabCtrlStyle_base.
	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
};
// 
struct TabCtrlStyle_VS2008_client_olive : TabCtrlStyle_VS2008_client_base
{		// TabCtrlStyle_VS2008_client_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool active, bool disable) override;
	COLORREF GetTabOutlineColor(TabCtrl const *ctrl, bool active, bool hover, bool disable, bool left) override;
	COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool active, bool hover, bool disable) override;
	COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool active, bool hover, bool disable) override;

		// TabCtrlStyle_base.
	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2008_bars_base : TabCtrlStyle_base
{		// TabCtrl::IRecalc.
	int GetBorderWidth(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetTabPadding(TabCtrl const *ctrl, IRecalc *base) override;

		// TabCtrl::Draw.
	void DrawControlAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;

		// TabCtrlStyle_base.
	void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	void DrawTabContext(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;   // draw image and text.
	COLORREF GetTabTextColor(TabCtrl const *ctrl, HANDLE tab) override;

	virtual COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool hover) = 0;
	virtual COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool hover, bool disable) = 0;
	virtual COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool hover, bool disable) = 0;
};
// 
struct TabCtrlStyle_VS2008_bars_classic : TabCtrlStyle_VS2008_bars_base
{		// TabCtrlStyle_VS2008_bars_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool hover) override;
	COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool hover, bool disable) override;
	COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool hover, bool disable) override;
};
// 
struct TabCtrlStyle_VS2008_bars_blue : TabCtrlStyle_VS2008_bars_base
{		// TabCtrlStyle_VS2008_bars_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool hover) override;
	COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool hover, bool disable) override;
	COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool hover, bool disable) override;
};
// 
struct TabCtrlStyle_VS2008_bars_silver : TabCtrlStyle_VS2008_bars_base
{		// TabCtrlStyle_VS2008_bars_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool hover) override;
	COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool hover, bool disable) override;
	COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool hover, bool disable) override;

		// TabCtrlStyle_base.
	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
};
// 
struct TabCtrlStyle_VS2008_bars_olive : TabCtrlStyle_VS2008_bars_base
{		// TabCtrlStyle_VS2008_bars_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool hover) override;
	COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool hover, bool disable) override;
	COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool hover, bool disable) override;

		// TabCtrlStyle_base.
	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2008_bars_custom1_base : TabCtrlStyle_VS2008_bars_base
{		// TabCtrl::IRecalc.
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetWindowsAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;

		// TabCtrl::Draw.
	void DrawControlAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
	void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
};
// 
struct TabCtrlStyle_VS2008_bars_classic_custom1 : TabCtrlStyle_VS2008_bars_custom1_base
{		// TabCtrlStyle_VS2008_bars_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool hover) override;
	COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool hover, bool disable) override;
	COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool hover, bool disable) override;
};
// 
struct TabCtrlStyle_VS2008_bars_blue_custom1 : TabCtrlStyle_VS2008_bars_custom1_base
{		// TabCtrlStyle_VS2008_bars_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool hover) override;
	COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool hover, bool disable) override;
	COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool hover, bool disable) override;
};
// 
struct TabCtrlStyle_VS2008_bars_silver_custom1 : TabCtrlStyle_VS2008_bars_custom1_base
{		// TabCtrlStyle_VS2008_bars_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool hover) override;
	COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool hover, bool disable) override;
	COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool hover, bool disable) override;

		// TabCtrlStyle_base.
	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
};
// 
struct TabCtrlStyle_VS2008_bars_olive_custom1 : TabCtrlStyle_VS2008_bars_custom1_base
{		// TabCtrlStyle_VS2008_bars_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl, bool hover) override;
	COLORREF GetTabGradientLightColor(TabCtrl const *ctrl, bool hover, bool disable) override;
	COLORREF GetTabGradientDarkColor(TabCtrl const *ctrl, bool hover, bool disable) override;

		// TabCtrlStyle_base.
	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Visual Studio 2010
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2010_client : TabCtrlStyle_base
{		// TabCtrl::IRecalc.
	int GetBorderWidth(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetWindowsAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetTabPadding(TabCtrl const *ctrl, IRecalc *base) override;

		// TabCtrl::Draw.
	void DrawControlAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
	void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;

		// TabCtrlStyle_base.
	COLORREF GetCtrlAreaBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabTextColor(TabCtrl const *ctrl, HANDLE tab) override;
	COLORREF GetEmptyWndsAreaBackColor(TabCtrl const *ctrl) override;
	COLORREF GetButtonCloseColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	COLORREF GetButtonMenuColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;

	virtual void DrawTabBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool top, bool active, bool select, bool hover);
	virtual void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool top, bool active);
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2010_client_custom1 : TabCtrlStyle_VS2010_client
{		// TabCtrlStyle_VS2010_client.
	void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2010_client_custom2 : TabCtrlStyle_VS2010_client
{		// TabCtrlStyle_VS2010_client.
	void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2010_bars : TabCtrlStyle_base
{		// TabCtrl::IRecalc.
	int GetBorderWidth(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetTabPadding(TabCtrl const *ctrl, IRecalc *base) override;

		// TabCtrl::Draw.
	void DrawControlAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;

		// TabCtrlStyle_base.
	COLORREF GetCtrlAreaBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabTextColor(TabCtrl const *ctrl, HANDLE tab) override;
	COLORREF GetEmptyWndsAreaBackColor(TabCtrl const *ctrl) override;
	COLORREF GetButtonCloseColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	COLORREF GetButtonMenuColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// Visual Studio 2019
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2019_client_base : TabCtrlStyle_base
{		// TabCtrl::IRecalc.
	int GetBorderWidth(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetWindowsAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;

		// TabCtrl::Draw.
	void DrawControlAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
	void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;

		// TabCtrlStyle_base.
	COLORREF GetTabSelectedBackColor(TabCtrl const *ctrl) override;
	void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	void DrawTabContext(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;

	virtual COLORREF GetTabHighlightedBackColor(TabCtrl const *ctrl) = 0;
	virtual COLORREF GetTabSelectedActiveBackColor(TabCtrl const *ctrl) = 0;
	virtual COLORREF GetTabSelectedPassiveBackColor(TabCtrl const *ctrl) = 0;
	virtual COLORREF GetButtonFrameHighlightBackColor(TabCtrl const *ctrl);
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2019_client_light : TabCtrlStyle_VS2019_client_base
{		// TabCtrlStyle_base.
	COLORREF GetCtrlAreaBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabTextColor(TabCtrl const *ctrl, HANDLE tab) override;
	COLORREF GetButtonCloseColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	COLORREF GetButtonMenuColor(TabCtrl const *ctrl, bool hover, bool pushed) override;

		// TabCtrlStyle_VS2019_client_base.
	COLORREF GetTabHighlightedBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabSelectedActiveBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabSelectedPassiveBackColor(TabCtrl const *ctrl) override;
	COLORREF GetButtonFrameHighlightBackColor(TabCtrl const *ctrl) override;
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2019_client_dark : TabCtrlStyle_VS2019_client_base
{		// TabCtrlStyle_base.
	COLORREF GetCtrlAreaBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabTextColor(TabCtrl const *ctrl, HANDLE tab) override;
	COLORREF GetButtonCloseColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	COLORREF GetButtonMenuColor(TabCtrl const *ctrl, bool hover, bool pushed) override;

		// TabCtrlStyle_VS2019_client_base.
	COLORREF GetTabHighlightedBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabSelectedActiveBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabSelectedPassiveBackColor(TabCtrl const *ctrl) override;
	COLORREF GetButtonFrameHighlightBackColor(TabCtrl const *ctrl) override;
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2019_client_blue : TabCtrlStyle_VS2019_client_base
{		// TabCtrl::IRecalc.
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetWindowsAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;

		// TabCtrl::Draw.
	void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;

		// TabCtrlStyle_base.
	COLORREF GetCtrlAreaBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabTextColor(TabCtrl const *ctrl, HANDLE tab) override;
	COLORREF GetButtonCloseColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	COLORREF GetButtonMenuColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;

		// TabCtrlStyle_VS2019_client_base.
	COLORREF GetTabHighlightedBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabSelectedActiveBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabSelectedPassiveBackColor(TabCtrl const *ctrl) override;

	virtual COLORREF GetTabNormalBackColor(TabCtrl const *ctrl);
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2019_bars_base : TabCtrlStyle_base
{		// TabCtrl::IRecalc.
	int GetBorderWidth(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetWindowsAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetTabPadding(TabCtrl const *ctrl, IRecalc *base) override;

		// TabCtrl::Draw.
	void DrawControlAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
	void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;

		// TabCtrlStyle_base.
	void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;

	virtual COLORREF GetTabHighlightedBackColor(TabCtrl const *ctrl) = 0;
	virtual COLORREF GetButtonFrameBackColorA(TabCtrl const *ctrl);
	virtual COLORREF GetButtonFrameBackColorB(TabCtrl const *ctrl);
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2019_bars_light : TabCtrlStyle_VS2019_bars_base
{		// TabCtrlStyle_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl) override;
	COLORREF GetCtrlAreaBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabSelectedBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabTextColor(TabCtrl const *ctrl, HANDLE tab) override;
	COLORREF GetButtonCloseColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	COLORREF GetButtonMenuColor(TabCtrl const *ctrl, bool hover, bool pushed) override;

		// TabCtrlStyle_VS2019_bars_base.
	COLORREF GetTabHighlightedBackColor(TabCtrl const *ctrl) override;
	COLORREF GetButtonFrameBackColorA(TabCtrl const *ctrl) override;
	COLORREF GetButtonFrameBackColorB(TabCtrl const *ctrl) override;
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2019_bars_dark : TabCtrlStyle_VS2019_bars_base
{		// TabCtrlStyle_base.
	COLORREF GetTabBorderColor(TabCtrl const *ctrl) override;
	COLORREF GetCtrlAreaBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabSelectedBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabTextColor(TabCtrl const *ctrl, HANDLE tab) override;
	COLORREF GetButtonCloseColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	COLORREF GetButtonMenuColor(TabCtrl const *ctrl, bool hover, bool pushed) override;

		// TabCtrlStyle_VS2019_bars_base.
	COLORREF GetTabHighlightedBackColor(TabCtrl const *ctrl) override;
	COLORREF GetButtonFrameBackColorA(TabCtrl const *ctrl) override;
	COLORREF GetButtonFrameBackColorB(TabCtrl const *ctrl) override;
};
/////////////////////////////////////////////////////////////////////////////
// 
struct TabCtrlStyle_VS2019_bars_blue : TabCtrlStyle_VS2019_bars_base
{		// TabCtrl::IRecalc.
	CRect GetControlAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetWindowsAreaPadding(TabCtrl const *ctrl, IRecalc *base) override;
	CRect GetTabPadding(TabCtrl const *ctrl, IRecalc *base) override;

		// TabCtrl::Draw.
	void DrawControlAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;
	void DrawWindowsAreaBack(TabCtrl const *ctrl, CDC *dc, CRect const *rect) override;

		// TabCtrlStyle_base.
	COLORREF GetCtrlAreaBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabSelectedBackColor(TabCtrl const *ctrl) override;
	COLORREF GetTabTextColor(TabCtrl const *ctrl, HANDLE tab) override;
	COLORREF GetButtonCloseColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	COLORREF GetButtonMenuColor(TabCtrl const *ctrl, bool hover, bool pushed) override;
	void DrawTabBack(TabCtrl const *ctrl, CDC *dc, HANDLE tab, CRect const *rect, CRgn *rgn) override;
	void DrawButtonFrame(TabCtrl const *ctrl, CDC *dc, CRect const *rect, bool hover, bool pushed) override;

		// TabCtrlStyle_VS2019_bars_base.
	COLORREF GetTabHighlightedBackColor(TabCtrl const *ctrl) override;

	virtual COLORREF GetTabNormalBackColor(TabCtrl const *ctrl);
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
template<typename CLASS_STYLE>
struct TabCtrlEx : TabCtrl
{	TabCtrlEx()
	{	style.Install(this);
	}
	CLASS_STYLE style;
};
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////







