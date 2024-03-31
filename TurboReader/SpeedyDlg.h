
// SpeedyDlg.h : header file
//

#pragma once
#include <string>
#include <vector>

// CSpeedyDlg dialog
class CSpeedyDlg : public CDialogEx
{
// Construction
public:
	CSpeedyDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPEEDY_DIALOG };
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


	// Timer ID
	static constexpr UINT_PTR s_nTimerID = 1;

	// Timer interval in milliseconds (e.g., change text every 1 second)
	static constexpr UINT s_nTimerInterval = 1000; // 1000 ms = 1 second
	static UINT s_nSpeed;

	// Timer handler function
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	void ReadWordsFromFile(const CString& filePath);
	UINT CalculateTimerValue(std::wstring str);
public:
	CString m_FilePath;
	static int index;
	CStatic m_Word;
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedPause();
	CSliderCtrl m_speed;
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedBookstackBtn();
};
