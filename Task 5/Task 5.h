
// Task 5.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTask5App:
// See Task 5.cpp for the implementation of this class
//

class CTask5App : public CWinApp
{
public:
	CTask5App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTask5App theApp;