
// Chapter1_LoadImg.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CChapter1_LoadImgApp:
// See Chapter1_LoadImg.cpp for the implementation of this class
//

class CChapter1_LoadImgApp : public CWinApp
{
public:
	CChapter1_LoadImgApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
protected:
	ULONG_PTR m_gdiplusToken;

public:
	virtual int ExitInstance();
};

extern CChapter1_LoadImgApp theApp;