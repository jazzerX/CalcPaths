
// CalcPathsDoc.cpp: реализация класса CCalcPathsDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "CalcPaths.h"
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

// Возвращает значение для х или у. Иначе бросает исключение
int CCalcPathsDoc::GetValue(XMLElement* value)
{
	if (value != nullptr)
	{
		XMLElement* valueList = value->ToElement();
		return value->IntText();
	}
	else
	{
		throw _T("Документ не валидный");
	}
}


Point CCalcPathsDoc::GetPoint(XMLElement* point)
{
	XMLElement* pointList = point->ToElement();
	Point res;

	res.m_nx = GetValue(pointList->FirstChildElement("x"));
	res.m_ny = GetValue(pointList->FirstChildElement("y"));

	return res;
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
		XMLElement* rootElement = doc.RootElement();
		XMLElement* w = rootElement->ToElement();
		for (XMLElement* obj = w->FirstChildElement(); obj != nullptr; obj = obj->NextSiblingElement())
		{
			if (std::strcmp(obj->Value(), "Windowsize") == 0)
			{
				// Здесь должен изменяться размер окна
				continue;
			}
			else
			{
				// Обрабатываем теги Objects
				XMLElement* figureList = obj->ToElement();
				for (XMLElement* figure = figureList->FirstChildElement(); figure != nullptr; figure = figure->NextSiblingElement())
				{
					if (std::strcmp(figure->Value(), "LineSegment") == 0)
					{
						Point sp, fp;
						XMLElement* pointList = figure->ToElement();

						try
						{
							sp = GetPoint(pointList->FirstChildElement("StartPoint"));
							fp = GetPoint(pointList->FirstChildElement("FinishPoint"));

							objList.emplace_back(std::move(std::make_shared<CLineSegment>(sp, fp, Type::LineSegment)));
						}
						catch (LPCTSTR exception)
						{
							AfxMessageBox(exception);
							m_vecOfPaths.clear();
							objList.clear();
							return;
						}
					}

					if (std::strcmp(figure->Value(), "Arc") == 0)
					{
						Point sp, mp, fp;
						XMLElement* pointList = figure->ToElement();

						try
						{
							sp = GetPoint(pointList->FirstChildElement("StartPoint"));
							mp = GetPoint(pointList->FirstChildElement("CenterPoint"));
							fp = GetPoint(pointList->FirstChildElement("FinishPoint"));
							objList.emplace_back(std::move(std::make_shared<CArc>(sp, mp, fp, Type::Arc)));
						}
						catch (LPCTSTR exception)
						{
							AfxMessageBox(exception);
							m_vecOfPaths.clear();
							objList.clear();
							return;
						}
					}
				}
			}
			m_vecOfPaths.emplace_back(std::move(objList));
			objList.clear();
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
