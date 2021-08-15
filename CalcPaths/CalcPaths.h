
// CalcPaths.h: основной файл заголовка для приложения CalcPaths
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CCalcPathsApp:
// Сведения о реализации этого класса: CalcPaths.cpp
//

class CCalcPathsApp : public CWinApp
{
public:
	CCalcPathsApp() noexcept;
	afx_msg void onBuildPath(UINT msg);

// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	UINT  m_nAppLook;

	afx_msg void OnAppAbout();



	DECLARE_MESSAGE_MAP()
};

extern CCalcPathsApp theApp;