// CBookStackDlg.cpp : implementation file
//

#include "pch.h"
#include "Speedy.h"
#include "afxdialogex.h"
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include "CBookStackDlg.h"


namespace fs = std::filesystem;


// CBookStackDlg dialog

IMPLEMENT_DYNAMIC(CBookStackDlg, CDialogEx)

CBookStackDlg::CBookStackDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FORMVIEW, pParent)
{

}

CBookStackDlg::~CBookStackDlg()
{
}

void CBookStackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_BOOK, m_BooksList);
}


BEGIN_MESSAGE_MAP(CBookStackDlg, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_BOOK, &CBookStackDlg::OnSelchangeListBook)
	ON_BN_CLICKED(IDC_BUTTON2, &CBookStackDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CBookStackDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CBookStackDlg message handlers


void CBookStackDlg::OnSelchangeListBook()
{
}


BOOL CBookStackDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	std::vector<std::wstring> files;
	std::wstring folder(TEXT("C:\\MyWorld\\TurboReader\\Books"));
	ReadFilesInFolder(folder, files);
	for (auto file : files)
	{
		m_BooksList.AddString(file.c_str());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CBookStackDlg::ReadFilesInFolder(const std::wstring& folderPath, std::vector<std::wstring>& files) {
	// Iterate over all files in the specified folder
	for (const auto& entry : fs::directory_iterator(folderPath)) {
		// Check if the current entry is a regular file
		if (entry.is_regular_file()) {

			if (entry.path().extension() == ".txt")
				files.push_back(entry.path().stem());
		}
	}
}


void CBookStackDlg::OnBnClickedButton2()
{
	int idx = m_BooksList.GetCurSel(); // Get the index of the selected item
	if (idx != LB_ERR) { // Check if an item is selected
		m_BooksList.GetText(idx, m_fileName); // Get the text of the selected item
	}

	CDialog::OnOK();
}


void CBookStackDlg::OnBnClickedButton1()
{
	CDialog::OnCancel();
}
