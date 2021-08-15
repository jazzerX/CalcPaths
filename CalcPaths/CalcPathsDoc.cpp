
// CalcPathsDoc.cpp: реализация класса CCalcPathsDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "CalcPaths.h"
#endif

//#import "msxml6.dll"
//using namespace MSXML2;



#include "CalcPathsDoc.h"

#include <propkey.h>

//#include "xml/tinyxml.h"
//#include "xml/tinystr.h"

#include "xml/tinyxml2.h"
using namespace tinyxml2;


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
	// TODO: добавьте код для одноразового вызова конструктора

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

void CCalcPathsDoc::OnFileOpen()
{
	m_vecOfPaths.clear();
	CFileDialog dlgFile(true, _T("xml"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_EXPLORER, _T("XML files (*.xml)|*.xml||"));
	dlgFile.DoModal();

	CString csPathName = dlgFile.GetPathName();
	CStringA filePath(csPathName);

	tinyxml2::XMLDocument doc;
	doc.LoadFile(filePath);

	if (doc.ErrorID() != XML_ERROR_FILE_NOT_FOUND && doc.ErrorID() != XML_ERROR_MISMATCHED_ELEMENT)
	{
		tinyxml2::XMLElement* rootElement = doc.RootElement();
		tinyxml2::XMLElement* w = rootElement->ToElement();
		
		for (tinyxml2::XMLElement* obj = w->FirstChildElement(); obj != nullptr; obj = obj->NextSiblingElement())
		{
			if (std::strcmp(obj->Value(), "Windowsize") == 0)
			{
				continue;
			}
			else
			{
				tinyxml2::XMLElement* figureList = obj->ToElement();
				for (tinyxml2::XMLElement* figure = figureList->FirstChildElement(); figure != nullptr; figure = figure->NextSiblingElement())
				{
					if (std::strcmp(figure->Value(), "LineSegment") == 0)
					{
						Point sp, fp;
						std::vector<int>vec;

						tinyxml2::XMLElement* pointList = figure->ToElement();
						for (tinyxml2::XMLElement* point = pointList->FirstChildElement(); point != nullptr; point = point->NextSiblingElement())
						{
							tinyxml2::XMLElement* valueList = point->ToElement();
							for (tinyxml2::XMLElement* val = valueList->FirstChildElement(); val != nullptr; val = val->NextSiblingElement())
								vec.emplace_back(val->IntText());
						}

						if (vec.size() == 4)
						{
							sp.m_nx = vec[0];
							sp.m_ny = vec[1];

							fp.m_nx = vec[2];
							fp.m_ny = vec[3];
						}
						else
						{
							AfxMessageBox(_T("Документ не валидный"));
							m_vecOfPaths.clear();
							return;
						}

						objList.emplace_back(std::move(std::make_shared<CLineSegment>(sp, fp, Type::LineSegment)));
					}

					if (std::strcmp(figure->Value(), "Arc") == 0)
					{
						Point sp, mp, fp;
						std::vector<int>vec;

						tinyxml2::XMLElement* pointList = figure->ToElement();
						for (tinyxml2::XMLElement* point = pointList->FirstChildElement(); point != nullptr; point = point->NextSiblingElement())
						{
							tinyxml2::XMLElement* valueList = point->ToElement();
							for (tinyxml2::XMLElement* val = valueList->FirstChildElement(); val != nullptr; val = val->NextSiblingElement())
								vec.emplace_back(val->IntText());
						}

						if (vec.size() == 6)
						{
							sp.m_nx = vec[0];
							sp.m_ny = vec[1];

							mp.m_nx = vec[2];
							mp.m_ny = vec[3];

							fp.m_nx = vec[4];
							fp.m_ny = vec[5];
						}
						else
						{
							AfxMessageBox(_T("Документ не валидный"));
							m_vecOfPaths.clear();
							return;
						}
						objList.emplace_back(std::move(std::make_shared<CArc>(sp, mp, fp, Type::Arc)));
					}
				}
			}
			m_vecOfPaths.emplace_back(std::move(objList));
			objList.clear();
		}
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
