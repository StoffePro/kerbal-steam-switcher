
// kerbal-steam-switcherDlg.h : header file
//

#pragma once
#include <afxcmn.h>
#include <string>
#include <experimental/filesystem>
#include <filesystem>



// CkerbalsteamswitcherDlg dialog
class CkerbalsteamswitcherDlg : public CDialogEx
{
// Construction
public:
	CkerbalsteamswitcherDlg(CWnd* pParent = nullptr);	// standard constructor
	void CKerbalsteamswitcherDlgPick(int row);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KERBALSTEAMSWITCHER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDblclkList1();
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
