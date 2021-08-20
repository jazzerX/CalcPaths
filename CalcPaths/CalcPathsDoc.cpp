
// CalcPathsDoc.cpp: реализация класса CCalcPathsDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "CalcPaths.h"
#include "MainFrm.h"
#endif


#include "CalcPathsDoc.h"

#include <propkey.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalcPathsDoc

IMPLEMENT_DYNCREATE(CCalcPathsDoc, CDocument)

BEGIN_MESSAGE_MAP(CCalcPathsDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CCalcPathsDoc::OnFileOpen)
END_MESSAGE_MAP()


// Создание или уничтожение CCalcPathsDoc

CCalcPathsDoc::CCalcPathsDoc() noexcept
{
	
}


CCalcPathsDoc::~CCalcPathsDoc()
{
	
}

BOOL CCalcPathsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}


// Сериализация CCalcPathsDoc

void CCalcPathsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{

	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

int CCalcPathsDoc::ParseToXML(Path& objList, tinyxml2::XMLElement* figure, Type type)
{
	try
	{
		switch (type)
		{
		case Type::LineSegment:
		{
			std::unique_ptr<CLineSegment> line = std::make_unique<CLineSegment>(CLineSegment::GetLine(figure));
			objList.m_path.emplace_back(std::move(line));
		}
		break;

		case Type::Arc:
		{
			std::unique_ptr<CArc> arc = std::make_unique<CArc>(CArc::GetLine(figure));
			objList.m_path.emplace_back(std::move(arc));
		}
		}

		return 0;
	}
	catch (LPCTSTR exception)
	{
		AfxMessageBox(exception);
		m_listOfPaths.clear();
		objList.m_path.clear();
		return -1;
	}
}

void CCalcPathsDoc::OnFileOpen()
{
	CString csPathName;

	CFileDialog dlgFile(true, _T("xml"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_EXPLORER, _T("XML files (*.xml)|*.xml||"));
	if (dlgFile.DoModal() == IDOK)
	{
		m_listOfPaths.clear();
		m_resultPath.clear();
		csPathName = dlgFile.GetPathName();
	}
	else 
		return;

	CStringA csaFilePath(csPathName);

	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(csaFilePath);

	if (xmlDoc.ErrorID() != tinyxml2::XML_ERROR_FILE_NOT_FOUND && xmlDoc.ErrorID() != tinyxml2::XML_ERROR_MISMATCHED_ELEMENT)
	{
		Path objList;

		tinyxml2::XMLElement* rootElement = xmlDoc.RootElement();
		tinyxml2::XMLElement* objects = rootElement->ToElement();

		for (tinyxml2::XMLElement* obj = objects->FirstChildElement(); obj != nullptr; obj = obj->NextSiblingElement())
		{
			if (std::strcmp(obj->Value(), "Windowsize") == 0)
			{
				// Считываем координаты из файла
				tinyxml2::XMLElement* figureList = obj->FirstChildElement("FinishPoint");
				tinyxml2::XMLElement* xVal = figureList->FirstChildElement("x");
				tinyxml2::XMLElement* yVal = figureList->FirstChildElement("y");

				int nWidth;
				int nHeight;

				if (xVal != nullptr && yVal != nullptr)
				{
					nWidth = xVal->IntText();
					nHeight = yVal->IntText();
				}
				else
				{
					AfxMessageBox(_T("Документ не валидный"));
					return;
				}

				// Определяем размер документа
				POSITION pos = GetFirstViewPosition();
				CRect crDocSize;
				GetNextView(pos)->GetClientRect(crDocSize);				

				// Находим главное окно
				CString csWndName;
				AfxGetMainWnd()->GetWindowTextW(csWndName);
				HWND wnd = FindWindow(nullptr, csWndName);

				// Получаем размер окна
				CRect crWndSize;
				GetWindowRect(wnd, crWndSize);

				int widthWnd = crWndSize.right - crWndSize.left;
				int heightWnd = crWndSize.bottom - crWndSize.top;

				// Считаем новый размер окна
				CRect crSize;
				crSize.right = (widthWnd - crDocSize.right) + nWidth + 1;
				crSize.bottom = (heightWnd - crDocSize.bottom) + nHeight + 1;

				// Размещаем окно по центру экрана
				int nPosX = ::GetSystemMetrics(SM_CXSCREEN) / 2 - crSize.right / 2;
				int nPosY = ::GetSystemMetrics(SM_CYSCREEN) / 2 - crSize.bottom / 2;

				// Меняем размер окна
				::SetWindowPos(wnd, nullptr, nPosX, nPosY, crSize.right, crSize.bottom, 0);
				AfxGetMainWnd()->RedrawWindow();
			}
			else
			{
				// Обрабатываем теги Objects
				tinyxml2::XMLElement* figureList = obj->ToElement();
				for (tinyxml2::XMLElement* figure = figureList->FirstChildElement(); figure != nullptr; figure = figure->NextSiblingElement())
				{
					if (std::strcmp(figure->Value(), "LineSegment") == 0)
						if (ParseToXML(objList, figure, Type::LineSegment) == -1)
							return;

					if (std::strcmp(figure->Value(), "Arc") == 0)
						if (ParseToXML(objList, figure, Type::Arc) == -1)
							return;
				}

				m_listOfPaths.emplace_back(std::make_shared<Path>(std::move(objList)));
				objList.m_path.clear();
			}
		}	
	}
	else
	{
		AfxMessageBox(_T("Документ не валидный"));
		return;
	}
}



#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CCalcPathsDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CCalcPathsDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CCalcPathsDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CCalcPathsDoc

#ifdef _DEBUG
void CCalcPathsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCalcPathsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CCalcPathsDoc
