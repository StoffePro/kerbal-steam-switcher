
// kerbal-steam-switcher.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include <vector>

#include "resource.h"		// main symbols

#define CKANREGKEY L"Software\\CKAN"
#define KERBALEXENAME L"KSP_x64.exe"

// CkerbalsteamswitcherApp:
// See kerbal-steam-switcher.cpp for the implementation of this class
//

class CkerbalsteamswitcherApp : public CWinApp
{
public:
	CkerbalsteamswitcherApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CkerbalsteamswitcherApp theApp;
