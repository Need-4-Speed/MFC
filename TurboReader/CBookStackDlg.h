#pragma once
#include "afxdialogex.h"


// CBookStackDlg dialog

class CBookStackDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookStackDlg)

public:
	CBookStackDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CBookStackDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void ReadFilesInFolder(const std::wstring& folderPath, std::vector<std::wstring>& files);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSelchangeListBook();
	CListBox m_BooksList;
	CString m_fileName;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
