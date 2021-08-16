#pragma once

#include <vector>
#include <string>
#include "Figures.h"
#include "BuildPaths.h"

#include "xml/tinyxml2.h"
using namespace tinyxml2;


class CCalcPathsDoc : public CDocument
{
protected: // создать только из сериализации
	CCalcPathsDoc() noexcept;
	DECLARE_DYNCREATE(CCalcPathsDoc)

private:
	Path objList;
// Атрибуты
public:
	Path m_resultPath;
	std::vector<Path> m_vecOfPaths;

private:
	int GetValue(XMLElement* value);
	Point GetPoint(XMLElement* point);

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

public:
	afx_msg void OnFileOpen();

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CCalcPathsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
