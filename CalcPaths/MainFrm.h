
// MainFrm.h: интерфейс класса CMainFrame
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // создать только из сериализации
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Атрибуты
public:
	int m_nWidth;
	int m_nHeight;

	int m_nPosX;
	int m_nPosY;

	LPCTSTR m_lpszWndName;

// Операции
public:

// Переопределение
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Реализация
public:
	virtual ~CMainFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // встроенные члены панели элементов управления
	CStatusBar        m_wndStatusBar;
	CMFCToolBar       m_wndToolBar;

// Созданные функции схемы сообщений
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

};


