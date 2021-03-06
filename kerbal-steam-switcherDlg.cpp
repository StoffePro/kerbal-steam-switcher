
// kerbal-steam-switcherDlg.cpp : implementation file
//

#include "stdafx.h"

#include <afxcmn.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include <experimental/filesystem> // C++-standard header file name  
#include <filesystem> // Microsoft-specific implementation header file name  
using namespace std::experimental::filesystem::v1;

#include "kerbal-steam-switcher.h"
#include "kerbal-steam-switcherDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CkerbalsteamswitcherDlg dialog



CkerbalsteamswitcherDlg::CkerbalsteamswitcherDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_KERBALSTEAMSWITCHER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CkerbalsteamswitcherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CkerbalsteamswitcherDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_DBLCLK(IDC_LIST1, &CkerbalsteamswitcherDlg::OnDblclkList1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CkerbalsteamswitcherDlg::OnLbnSelchangeList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CkerbalsteamswitcherDlg::OnNMDblclkList2)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST2, &CkerbalsteamswitcherDlg::OnLvnItemchangedList2)
	ON_BN_CLICKED(IDOK, &CkerbalsteamswitcherDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CkerbalsteamswitcherDlg message handlers

BOOL CkerbalsteamswitcherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	HKEY hCkan = NULL;

	LONG retCode = RegOpenKeyEx(HKEY_CURRENT_USER, CKANREGKEY, 0, KEY_QUERY_VALUE, &hCkan);

	if (retCode != ERROR_SUCCESS)
	{
		MessageBox(_wcserror(errno), L"RegOpenKeyEx", MB_OK);
		exit(1);
	}
	DWORD numValues = 0, maxValueNameLen = 0;
	retCode = RegQueryInfoKey(
		hCkan,				// HKEY      hKey,
		NULL,				// LPTSTR    lpClass,
		NULL,				// LPDWORD   lpcClass,
		NULL,				// LPDWORD   lpReserved,
		NULL,				// LPDWORD   lpcSubKeys,
		NULL,				// LPDWORD   lpcMaxSubKeyLen,
		NULL,				// LPDWORD   lpcMaxClassLen,
		&numValues,			// LPDWORD   lpcValues,
		&maxValueNameLen,	// LPDWORD   lpcMaxValueNameLen,
		NULL,				// LPDWORD   lpcMaxValueLen,
		NULL,				// LPDWORD   lpcbSecurityDescriptor,
		NULL);				// PFILETIME lpftLastWriteTime
	if (retCode != ERROR_SUCCESS)
	{
		MessageBox(_wcserror(errno), L"RegQueryInfoKey", MB_OK);
		exit(1);
	}
	maxValueNameLen++;

	LPWSTR valueName = new wchar_t[maxValueNameLen];
	LPWSTR d = NULL;
	DWORD n, v_t, d_l;
	std::vector<std::pair<std::wstring, std::wstring>> KerbalInstances;

	CListCtrl* list2 = (CListCtrl*)GetDlgItem(IDC_LIST2);
	LPWSTR instanceName = NULL, instancePath = NULL;

	LVCOLUMN col = LVCOLUMN();
	col.mask = LVCF_FMT | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT;
	col.iSubItem = 0;
	list2->InsertColumn(0, &col);

	col.iSubItem = 1;
	list2->InsertColumn(1, &col);

	for (DWORD i = 0; i < numValues; i++)
	{
		n = maxValueNameLen;
		retCode = RegEnumValue(
			hCkan,		// HKEY    hKey,
			i,			// DWORD   dwIndex,
			valueName,	// LPTSTR  lpValueName,
			&n,			// LPDWORD lpcchValueName,
			NULL,		// LPDWORD lpReserved,
			&v_t,		// LPDWORD lpType,
			NULL,		// LPBYTE  lpData,
			&d_l);		// LPDWORD lpcbData
		if (retCode != ERROR_SUCCESS)
		{
			MessageBox(_wcserror(errno), L"RegEnumValue", MB_OK);
			exit(1);
		}

		if (v_t != REG_SZ)
		{
			continue;
		}

		if (!_wcsnicmp(valueName, L"KSPInstanceName_", lstrlenW(L"KSPInstanceName_")))
		{
			retCode = RegGetValue(
				hCkan,			// HKEY    hkey,
				NULL,			// LPCTSTR lpSubKey,
				valueName,		// LPCTSTR lpValue,
				RRF_RT_REG_SZ,	// DWORD   dwFlags,
				NULL,			// LPDWORD pdwType,
				NULL,			// PVOID   pvData,
				&d_l);			// LPDWORD pcbData
			if (retCode != ERROR_SUCCESS)
			{
				MessageBox(_wcserror(retCode), L"RegGetValue", MB_OK);
				exit(1);
			}

			d = new wchar_t[d_l];
			retCode = RegGetValue(
				hCkan,			// HKEY    hkey,
				NULL,			// LPCTSTR lpSubKey,
				valueName,		// LPCTSTR lpValue,
				RRF_RT_REG_SZ,	// DWORD   dwFlags,
				NULL,			// LPDWORD pdwType,
				d,				// PVOID   pvData,
				&d_l);			// LPDWORD pcbData
			if (retCode != ERROR_SUCCESS)
			{
				MessageBox(_wcserror(errno), L"RegGetValue", MB_OK);
				exit(1);
			}
			instanceName = new wchar_t[wcslen(d) + 1];
			wcscpy(instanceName, d);
			
			// I know this is stupid.
			valueName[11] = L'P';
			valueName[12] = L'a';
			valueName[13] = L't';
			valueName[14] = L'h';

			retCode = RegGetValue(
				hCkan,			// HKEY    hkey,
				NULL,			// LPCTSTR lpSubKey,
				valueName,		// LPCTSTR lpValue,
				RRF_RT_REG_SZ,	// DWORD   dwFlags,
				NULL,			// LPDWORD pdwType,
				NULL,			// PVOID   pvData,
				&d_l);			// LPDWORD pcbData
			if (retCode != ERROR_SUCCESS)
			{
				MessageBox(_wcserror(retCode), L"RegGetValue", MB_OK);
				exit(1);
			}

			d = new wchar_t[d_l];
			retCode = RegGetValue(
				hCkan,			// HKEY    hkey,
				NULL,			// LPCTSTR lpSubKey,
				valueName,		// LPCTSTR lpValue,
				RRF_RT_REG_SZ,	// DWORD   dwFlags,
				NULL,			// LPDWORD pdwType,
				d,				// PVOID   pvData,
				&d_l);			// LPDWORD pcbData
			if (retCode != ERROR_SUCCESS)
			{
				MessageBox(_wcserror(errno), L"RegGetValue", MB_OK);
				exit(1);
			}
			instancePath = new wchar_t[wcslen(d) + 1];
			wcscpy(instancePath, d);

			if (exists(instancePath))
			{
				LVITEM item = LVITEM();
				item.mask = LVIF_TEXT | LVIF_PARAM;
				item.iItem = 0;
				item.pszText = instanceName;
				//item.lParam = (LPARAM)exdata.c_str();
				list2->InsertItem(&item);
				list2->SetItemText(0, 1, instancePath);
			}
		}
	}



	for (int i = 0; i < list2->GetHeaderCtrl()->GetItemCount(); i++)
	{
		list2->SetColumnWidth(i, LVSCW_AUTOSIZE);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CkerbalsteamswitcherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CkerbalsteamswitcherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CkerbalsteamswitcherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CkerbalsteamswitcherDlg::OnDblclkList1()
{
	// TODO: Add your control notification handler code here
}


void CkerbalsteamswitcherDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}

void CkerbalsteamswitcherDlg::CKerbalsteamswitcherDlgPick(int row)
{
	CListCtrl* list2 = (CListCtrl*)GetDlgItem(IDC_LIST2);
	std::wstring KerbalPath = list2->GetItemText(row, 1);
	path KerbalExePath(KerbalPath);
	KerbalExePath.append(KERBALEXENAME);
	wchar_t *execarglist[] = { NULL, NULL };
	execarglist[0] = new wchar_t[KerbalExePath._Mystr.capacity() + 1];
	wcscpy(execarglist[0], &KerbalExePath.wstring()[0]);
	
	if (!SetCurrentDirectory(KerbalExePath.parent_path().c_str()))
	{
		MessageBox(L"Failed CD", L"Aaargh!", MB_OK);
		exit(1);
	}
	_wexecv(execarglist[0], execarglist);
	MessageBox(_wcserror(errno), L"ERROR", MB_OK);
	exit(1);
}

void CkerbalsteamswitcherDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	this->AnimateWindow(200, AW_HIDE);
	*pResult = 0;
	CKerbalsteamswitcherDlgPick(pNMItemActivate->iItem);}


void CkerbalsteamswitcherDlg::OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CkerbalsteamswitcherDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CListCtrl* list2 = (CListCtrl*)GetDlgItem(IDC_LIST2);
	CKerbalsteamswitcherDlgPick(list2->GetSelectionMark());

	CDialogEx::OnOK();
}
