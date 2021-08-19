
// CalcPathsView.h: интерфейс класса CCalcPathsView
//

#pragma once

#include "BuildPaths.h"

#include "gdidrawer.h"

class CCalcPathsView : public CView
{
protected: // создать только из сериализации
	CCalcPathsView() noexcept;
	DECLARE_DYNCREATE(CCalcPathsView)

// Атрибуты
public:
	CCalcPathsDoc* GetDocument() const;

private:
	std::unique_ptr<IDrawer> m_drawer;
	std::list<PathPtr> m_resultPath;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	afx_msg void onBuildPath(UINT msg);

	void onClearDoc();

// Реализация
public:
	virtual ~CCalcPathsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // версия отладки в CalcPathsView.cpp
inline CCalcPathsDoc* CCalcPathsView::GetDocument() const
   { return reinterpret_cast<CCalcPathsDoc*>(m_pDocument); }
#endif

