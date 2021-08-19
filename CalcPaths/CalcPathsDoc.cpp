
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

// Возвращает значение для х или у. Иначе бросает исключение

void CCalcPathsDoc::OnFileOpen()
{
	CString csPathName;

	CFileDialog dlgFile(true, _T("xml"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_EXPLORER, _T("XML files (*.xml)|*.xml||"));
	if (dlgFile.DoModal() == IDOK)
	{
		m_listOfPaths.clear();
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
				/*Меняем размер окна*/

				tinyxml2::XMLElement* figureList = obj->FirstChildElement("FinishPoint");
				int nWidth;
				int nHeight;

				tinyxml2::XMLElement* xVal = figureList->FirstChildElement("x");
				tinyxml2::XMLElement* yVal = figureList->FirstChildElement("y");

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

				POSITION pos = GetFirstViewPosition();
				CRect crDocSize;
				GetNextView(pos)->GetClientRect(crDocSize);				

				HWND wnd = FindWindow(nullptr, _T("Расчет путей"));

				CRect crWndSize;
				GetWindowRect(wnd, crWndSize);

				int widthWnd = crWndSize.right - crWndSize.left;
				int heightWnd = crWndSize.bottom - crWndSize.top;

				CRect crSize;
				crSize.right = (widthWnd - crDocSize.right) + nWidth;
				crSize.bottom = (heightWnd - crDocSize.bottom) + nHeight;

				int nPosX = ::GetSystemMetrics(SM_CXSCREEN) / 2 - nWidth / 2;
				int nPosY = ::GetSystemMetrics(SM_CYSCREEN) / 2 - nHeight / 2;

				::SetWindowPos(wnd, HWND_TOPMOST, nPosX, nPosY, crSize.right, crSize.bottom, SWP_NOZORDER);
			}
			else
			{
				// Обрабатываем теги Objects
				tinyxml2::XMLElement* figureList = obj->ToElement();
				for (tinyxml2::XMLElement* figure = figureList->FirstChildElement(); figure != nullptr; figure = figure->NextSiblingElement())
				{
					if (std::strcmp(figure->Value(), "LineSegment") == 0)
					{
						try
						{
							Point sp, fp;
							tinyxml2::XMLElement* pointList = figure->ToElement();

							sp = CLineSegment::GetPoint(pointList->FirstChildElement("StartPoint"));
							fp = CLineSegment::GetPoint(pointList->FirstChildElement("FinishPoint"));

							objList.m_path.emplace_back(std::move(std::make_unique<CLineSegment>(sp, fp, Type::LineSegment)));
						}
						catch (LPCTSTR exception)
						{
							AfxMessageBox(exception);
							m_listOfPaths.clear();
							objList.m_path.clear();
							return;
						}
					}

					if (std::strcmp(figure->Value(), "Arc") == 0)
					{
						try
						{
							Point sp, mp, fp;
							tinyxml2::XMLElement* pointList = figure->ToElement();

							sp = CArc::GetPoint(pointList->FirstChildElement("StartPoint"));
							mp = CArc::GetPoint(pointList->FirstChildElement("CenterPoint"));
							fp = CArc::GetPoint(pointList->FirstChildElement("FinishPoint"));

							objList.m_path.emplace_back(std::move(std::make_unique<CArc>(sp, mp, fp, Type::Arc)));
						}
						catch (LPCTSTR exception)
						{
							AfxMessageBox(exception);
							m_listOfPaths.clear();
							objList.m_path.clear();
							return;
						}
					}
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
