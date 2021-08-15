
// CalcPathsView.cpp: реализация класса CCalcPathsView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "CalcPaths.h"
#endif

#include "CalcPathsDoc.h"
#include "CalcPathsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCalcPathsView


IMPLEMENT_DYNCREATE(CCalcPathsView, CView)

BEGIN_MESSAGE_MAP(CCalcPathsView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// Создание или уничтожение CCalcPathsView

CCalcPathsView::CCalcPathsView() noexcept
{
	// TODO: добавьте код создания

}

CCalcPathsView::~CCalcPathsView()
{
}

BOOL CCalcPathsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CCalcPathsView

void CCalcPathsView::OnDraw(CDC* pDC)
{
	CCalcPathsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

}

// Печать CCalcPathsView

BOOL CCalcPathsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CCalcPathsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CCalcPathsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CCalcPathsView

#ifdef _DEBUG
void CCalcPathsView::AssertValid() const
{
	CView::AssertValid();
}

void CCalcPathsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCalcPathsDoc* CCalcPathsView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCalcPathsDoc)));
	return (CCalcPathsDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CCalcPathsView
