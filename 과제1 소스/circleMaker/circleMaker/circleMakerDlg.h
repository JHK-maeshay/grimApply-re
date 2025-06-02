
// circleMakerDlg.h : header file
//

#pragma once
#include <vector>


// CcircleMakerDlg dialog
class CcircleMakerDlg : public CDialogEx
{
// Construction
public:
	CcircleMakerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CIRCLEMAKER_DIALOG };
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

	//buttons
public:
	afx_msg void OnBnClickedSetRadius();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedRandom();
	void UpdateClickPointUI();

	DECLARE_MESSAGE_MAP()
private:
	int radius = 10;  // radius
	int borderWidth = 2;
	struct PointCircle {
		CPoint center;
		bool selected = false; // detect drag
	};
	std::vector<PointCircle> clickPoints; // detect point
};
