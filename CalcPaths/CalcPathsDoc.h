#pragma once

#include <vector>
#include <string>

#include "Figures.h"
#include "LineSegment.h"
#include "Arc.h"

#include "BuildPaths.h"



class CCalcPathsDoc : public CDocument
{
protected: // создать только из сериализации
	CCalcPathsDoc() noexcept;
	DECLARE_DYNCREATE(CCalcPathsDoc)

private:

// Атрибуты
public:
	std::shared_ptr<Path> m_resultPath;
	std::list<Path> m_vecOfPaths;


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
