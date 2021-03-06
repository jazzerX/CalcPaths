
// MainFrm.h: интерфейс класса CMainFrame
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // создать только из сериализации
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

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

public:  // встроенные члены панели элементов управления
	CStatusBar        m_wndStatusBar;

// Созданные функции схемы сообщений
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

};


