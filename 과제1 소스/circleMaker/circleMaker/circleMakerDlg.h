
// circleMakerDlg.h : header file
//

#pragma once
#include <vector>
#include "afxwin.h"
#include "atlimage.h"

// CcircleMakerDlg dialog
class CcircleMakerDlg : public CDialogEx
{
// Construction
private:
	CImage m_image;
	BOOL validImgPos(int x, int y);
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
	void UpdateDisplay();
	afx_msg void OnBnClickedSetRadius();
	afx_msg void OnBnClickedReset();
	afx_msg void OnBnClickedRandom();
	
private:
	void UpdateClickPointUI(); // click event

	int m_radius = 10;  // radius
	int borderWidth = 2;
	struct PointCircle {
		CPoint center;
		bool selected = false; // click point tracker
	};
	int m_border = 5;
	void OnBnClickedSetBorder(); // border
	std::vector<PointCircle> m_clickPoints; // detect point
	void drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius); //draw circle
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point); //draw trigger
	void makeHollowCircle(); //draw border circle
	void drawHollowCircleSafe(unsigned char* fm, int x, int y, int nRadius, int nGray); //check circle crop

	bool m_isDragging = false;
	int m_selectedPointIndex = -1;//drag control
	ULONGLONG m_lastUpdateTime = 0;

	void OnMouseMove(UINT nFlags, CPoint point);//drag func
	void OnLButtonUp(UINT nFlags, CPoint point);//drag end

	DECLARE_MESSAGE_MAP()
};