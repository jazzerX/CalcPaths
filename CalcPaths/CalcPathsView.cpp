
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
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)

	ON_COMMAND_RANGE(ID_SHORTEST_PATH, ID_ALL_PATHS, &CCalcPathsView::onBuildPath)

END_MESSAGE_MAP()

// Создание или уничтожение CCalcPathsView

CCalcPathsView::CCalcPathsView() noexcept
{
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

	m_drawer = std::make_unique<CGDIDrawer>(pDC);

	for (const auto& path: m_resultPath)
		if (path.lock() != nullptr)
			for (auto& figure : path.lock()->m_path)
				figure->Draw(m_drawer);
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

void CCalcPathsView::onBuildPath(UINT msg)
{
	CCalcPathsDoc* pDoc = GetDocument();

	if (pDoc->m_listOfPaths.size() == 0)
	{
		AfxMessageBox(_T("Не удалось выполнить команду"));
		return;
	}

	std::unique_ptr<Task> task;

	switch (msg)
	{
	case ID_SHORTEST_PATH:
		task = std::make_unique<Task>(std::make_unique<ShortestPath>());
		break;
	case ID_LONGEST_PATH:
		task = std::make_unique<Task>(std::make_unique<LongestPath>());
		break;
	case ID_ONLY_LINES:
		task = std::make_unique<Task>(std::make_unique<OnlyLines>());
		break;
	case ID_ONLY_ARCS:
		task = std::make_unique<Task>(std::make_unique<OnlyArcs>());
		break;
	case ID_ALL_PATHS:
		task = std::make_unique<Task>(std::make_unique<AllPaths>());
		break;	
	case ID_CLEAR_DOCUMENT:
		onClearDoc();
		return;
	}

	onClearDoc();
	m_resultPath = task->Run(pDoc->m_listOfPaths);

	if (m_resultPath.empty())
	{
		AfxMessageBox(_T("Не удалось построить путь"));
		return;
	}

	CClientDC aDc(this);
	OnDraw(&aDc);
}

void CCalcPathsView::onClearDoc()
{
	m_resultPath.clear();
	CWnd::Invalidate(TRUE);
	CWnd::UpdateWindow();
}

