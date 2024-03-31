
// SpeedyDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Speedy.h"
#include "SpeedyDlg.h"
#include "afxdialogex.h"
#include <afx.h>
#include <afxwin.h>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include "CBookStackDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static std::vector<std::wstring> words; // Vector to store words
int CSpeedyDlg::index = 0;
UINT CSpeedyDlg::s_nSpeed = 1;

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


// CSpeedyDlg dialog



CSpeedyDlg::CSpeedyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SPEEDY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpeedyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_WORD, m_Word);
	DDX_Control(pDX, IDC_SLIDER1, m_speed);
}

BEGIN_MESSAGE_MAP(CSpeedyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CSpeedyDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDPAUSE, &CSpeedyDlg::OnBnClickedPause)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSpeedyDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_BOOKSTACK_BTN, &CSpeedyDlg::OnBnClickedBookstackBtn)
END_MESSAGE_MAP()


// CSpeedyDlg message handlers

BOOL CSpeedyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);


	// Assume you have a button control with the ID IDC_MY_BUTTON
	CButton* pButtonBookStack = (CButton*)GetDlgItem(IDC_BOOKSTACK_BTN);
	if (pButtonBookStack) {
		// Load the icon resource
		HICON hIcon = AfxGetApp()->LoadIcon(IDR_ICON_BOOK); // Replace IDI_MY_ICON with your icon resource ID

		// Set the icon to the button
		pButtonBookStack->SetIcon(hIcon);
	}

	// Assume you have a button control with the ID IDC_MY_BUTTON
	CButton* pButtonClose = (CButton*)GetDlgItem(IDC_BUTTON_CLOSE);
	if (pButtonClose) {
		// Load the icon resource
		HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON_CLOSE); // Replace IDI_MY_ICON with your icon resource ID

		// Set the icon to the button
		pButtonClose->SetIcon(hIcon);
	}


	CFont* m_cfont = new CFont();
	m_cfont->CreatePointFont(600, _T("Lucida Sans"));
	m_Word.SetFont(m_cfont); //C_Word is a control variable for the Static text control

	// Initialize slider control
	m_speed.SetRange(1, 4); // Set slider range
	m_speed.SetPos(1); // Set initial position


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

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSpeedyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSpeedyDlg::OnPaint()
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
HCURSOR CSpeedyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSpeedyDlg::OnTimer(UINT_PTR nIDEvent) {
	if (nIDEvent == s_nTimerID) {
		if (index < words.size())
		{
			std::wstring str = words[index];

			m_Word.SetWindowTextW(str.c_str());

			SetTimer(s_nTimerID, CalculateTimerValue(words[index]), nullptr);
			index++;
		}
		else
		{
			// All words displayed, stop the timer
			KillTimer(s_nTimerID);
			index = 0;
		}
	}

	CDialog::OnTimer(nIDEvent);
}



void CSpeedyDlg::OnBnClickedStart()
{
	KillTimer(s_nTimerID);
	if (m_FilePath.GetLength())
	{
		ReadWordsFromFile(m_FilePath);
		// Start the timer
		SetTimer(s_nTimerID, CalculateTimerValue(words[index]), nullptr);
	}
}


void CSpeedyDlg::ReadWordsFromFile(const CString& filePath)
{
	std::wifstream file(filePath); // Open the file for reading
	if (!file.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return;
	}

	std::wstring line;
	while (std::getline(file, line)) { // Read each line from the file
		std::wistringstream iss(line); // Create a string stream from the line
		std::wstring word;
		while (iss >> word) { // Extract words from the line
			words.push_back(word); // Store each word in the vector
		}
	}

	file.close(); // Close the file
}


void CSpeedyDlg::OnBnClickedPause()
{
	KillTimer(s_nTimerID);
}


UINT CSpeedyDlg::CalculateTimerValue(std::wstring str)
{
	UINT timer = 100;
	if (str.size() < 4)
	{
		timer = 700 / s_nSpeed;
	}
	else if (str.size() < 10)
	{
		timer = str.size() * (300/ s_nSpeed);
	}
	else if (str.size() < 20)
	{

		timer = str.size() * (400 / s_nSpeed);
	}
	else
	{
		timer = 10* (1000/s_nSpeed);
	}
	return timer;
}

void CSpeedyDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER1) {
		// Slider control has been scrolled
		s_nSpeed = m_speed.GetPos(); // Get current position
		if (words.size() > 0 && index <= words.size())
			SetTimer(s_nTimerID, CalculateTimerValue(words[index-1]), nullptr);
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CSpeedyDlg::OnBnClickedClose()
{
	KillTimer(s_nTimerID);
	CDialog::OnCancel();
}


void CSpeedyDlg::OnBnClickedBookstackBtn()
{
	KillTimer(s_nTimerID);
	CBookStackDlg bookDlg;
	INT_PTR nResponse = bookDlg.DoModal();
	if (nResponse == IDOK)
	{
		m_FilePath = _T("");
		m_FilePath.Append(TEXT("C:\\MyWorld\\TurboReader\\Books\\"));
		m_FilePath.Append(bookDlg.m_fileName);
		m_FilePath.Append(TEXT(".txt"));
		index = 0;
	}
}


