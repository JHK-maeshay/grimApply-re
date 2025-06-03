
// circleMakerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "circleMaker.h"
#include "circleMakerDlg.h"
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


// CcircleMakerDlg dialog



CcircleMakerDlg::CcircleMakerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CIRCLEMAKER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcircleMakerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CcircleMakerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	//click event
	ON_WM_LBUTTONDOWN()

	//drag event
	ON_WM_MOUSEMOVE()

	//release event
	ON_WM_LBUTTONUP()

	//buttons
	ON_BN_CLICKED(IDC_BTN_SET_RADIUS, &CcircleMakerDlg::OnBnClickedSetRadius)
	ON_BN_CLICKED(IDC_BTN_SET_BORDER, &CcircleMakerDlg::OnBnClickedSetBorder)
	ON_BN_CLICKED(IDC_BTN_RESET, &CcircleMakerDlg::OnBnClickedReset)
	ON_BN_CLICKED(IDC_BTN_RANDOM, &CcircleMakerDlg::OnBnClickedRandom)
END_MESSAGE_MAP()


// CcircleMakerDlg message handlers

BOOL CcircleMakerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	SetDlgItemText(IDC_EDIT_RADIUS, _T("10"));
	SetDlgItemText(IDC_EDIT_BORDER, _T("5"));
	SetDlgItemText(IDC_STATIC_POS1, _T("Point 1: ( , )"));
	SetDlgItemText(IDC_STATIC_POS2, _T("Point 2: ( , )"));
	SetDlgItemText(IDC_STATIC_POS3, _T("Point 3: ( , )"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CcircleMakerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CcircleMakerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		if (!m_image.IsNull())
		{
			m_image.Draw(dc, 0, 0);
		}
		else
		{
			CDialogEx::OnPaint();
		}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CcircleMakerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 이미지 판별 함수
BOOL CcircleMakerDlg::validImgPos(int x, int y)
{
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(x, y));
}

// 출력 함수
void CcircleMakerDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

//SET RADIUS 버튼 함수
void CcircleMakerDlg::OnBnClickedSetRadius()
{
	//원 그려져있을때 실행 종료
	if (!m_clickPoints.empty())
	{
		AfxMessageBox(_T("RESET을 먼저 해주세요!"));
		return;
	}

	//초기화 함수
	CRect rect;
	GetClientRect(&rect);
	int nWidth = rect.Width();
	int nHeight = rect.Height();
	int nBpp = 8;

	if (!m_image.IsNull())
	{
		m_image.Destroy();
	}//기존 이미지 제거

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	UpdateDisplay();

	Invalidate(FALSE);



	CString str;
	GetDlgItemText(IDC_EDIT_RADIUS, str);
	int r = _ttoi(str);
	if (r > 0)
	{
		m_radius = r;
	}
	else
	{
		AfxMessageBox(_T("유효한 값을 입력하세요!"));
	}
}

//SET BORDER 버튼 함수
void CcircleMakerDlg::OnBnClickedSetBorder()
{
	CString str;
	GetDlgItemText(IDC_EDIT_BORDER, str);
	int border = _ttoi(str);
	if (border > 0)
	{
		m_border = border;
	}
	else
	{
		AfxMessageBox(_T("유효한 값을 입력하세요!"));
	}
}

void CcircleMakerDlg::OnBnClickedReset() {
	CRect rect;
    GetClientRect(&rect);
    int nWidth = rect.Width();
    int nHeight = rect.Height();
    int nBpp = 8;

    if (!m_image.IsNull())
    {
        m_image.Destroy();
    }

    m_image.Create(nWidth, -nHeight, nBpp);

	// set palette
	RGBQUAD rgb[256];
	for (int i = 0; i < 256; i++)
	{
		rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
	}
	m_image.SetColorTable(0, 256, rgb);
	//

    int nPitch = m_image.GetPitch();
    unsigned char* fm = (unsigned char*)m_image.GetBits();
    memset(fm, 0xFF, nPitch * nHeight);

    m_clickPoints.clear();

    SetDlgItemText(IDC_STATIC_POS1, _T("Point 1: ( , )"));
    SetDlgItemText(IDC_STATIC_POS2, _T("Point 2: ( , )"));
    SetDlgItemText(IDC_STATIC_POS3, _T("Point 3: ( , )"));

    Invalidate(FALSE);
}

void CcircleMakerDlg::OnBnClickedRandom() {

}

//detect point
void CcircleMakerDlg::UpdateClickPointUI()
{
	CString str;
	if (m_clickPoints.size() > 0)
	{
		str.Format(_T("Point 1: (%d, %d)"), m_clickPoints[0].center.x, m_clickPoints[0].center.y);
		SetDlgItemText(IDC_STATIC_POS1, str);
	}
	if (m_clickPoints.size() > 1)
	{
		str.Format(_T("Point 2: (%d, %d)"), m_clickPoints[1].center.x, m_clickPoints[1].center.y);
		SetDlgItemText(IDC_STATIC_POS2, str);
	}
	if (m_clickPoints.size() > 2)
	{
		str.Format(_T("Point 3: (%d, %d)"), m_clickPoints[2].center.x, m_clickPoints[2].center.y);
		SetDlgItemText(IDC_STATIC_POS3, str);
	}
}

// draw circle
void CcircleMakerDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();


	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (isInCircle(i, j, nCenterX, nCenterY, nRadius))
				fm[j*nPitch + i] = nGray;
		}
	}
}

bool CcircleMakerDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius*nRadius) {
		bRet = true;
	}

	return bRet;
}

//draw border circle
void CcircleMakerDlg::makeHollowCircle()
{
	if (m_clickPoints.size() < 3)
		return;  // check 3 point

	CPoint p1 = m_clickPoints[0].center;
	CPoint p2 = m_clickPoints[1].center;
	CPoint p3 = m_clickPoints[2].center;

	double A = p2.x - p1.x;
	double B = p2.y - p1.y;
	double C = p3.x - p1.x;
	double D = p3.y - p1.y;

	double E = A * (p1.x + p2.x) + B * (p1.y + p2.y);
	double F = C * (p1.x + p3.x) + D * (p1.y + p3.y);
	double G = 2.0 * (A * (p3.y - p2.y) - B * (p3.x - p2.x));

	double centerX = (D * E - B * F) / G;
	double centerY = (A * F - C * E) / G;
	double radius = sqrt((p1.x - centerX) * (p1.x - centerX) +
		(p1.y - centerY) * (p1.y - centerY));

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	// flush
	memset(fm, 0xFF, nPitch * m_image.GetHeight());

	// draw circles
	for (int i = 0; i < m_clickPoints.size(); i++)
	{
		CPoint center = m_clickPoints[i].center;
		drawCircle(fm, center.x - m_radius, center.y - m_radius, m_radius, 80);
	}

	// draw hollow circles
	drawHollowCircleSafe(fm, static_cast<int>(centerX - radius), static_cast<int>(centerY - radius),
		static_cast<int>(radius), 80);

	Invalidate(FALSE);
	UpdateClickPointUI();
}

//check circle cropp
void CcircleMakerDlg::drawHollowCircleSafe(unsigned char* fm, int x, int y, int nRadius, int nGray)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();
	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();

	int borderThickness = m_border;  // input
	int halfThickness = borderThickness / 2;

	// 짝수일 때 남는 1두께를 안쪽으로
	int innerRadius = nRadius - halfThickness;
	int outerRadius = nRadius + (borderThickness - halfThickness);

	for (int j = y - borderThickness; j < y + nRadius * 2 + borderThickness; j++) {
		for (int i = x - borderThickness; i < x + nRadius * 2 + borderThickness; i++) {
			if (i < 0 || i >= nWidth || j < 0 || j >= nHeight)
				continue;

			if (isInCircle(i, j, nCenterX, nCenterY, outerRadius)) {
				if (!isInCircle(i, j, nCenterX, nCenterY, innerRadius)) {
					fm[j * nPitch + i] = nGray;
				}
			}
		}
	}
}

// click event
void CcircleMakerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);

	if (m_image.IsNull())
	{
		AfxMessageBox(_T("SET RADIUS 를 먼저 진행하세요!"));
		return;
	}

	// drag event
	for (int i = 0; i < m_clickPoints.size(); i++)
	{

		CPoint center = m_clickPoints[i].center;
		int dx = point.x - center.x;
		int dy = point.y - center.y;
		if (abs(dx) <= m_radius && abs(dy) <= m_radius)
		{
			m_isDragging = true;
			m_selectedPointIndex = i;
			m_lastUpdateTime = GetTickCount64();
			SetCapture();
			return; // goto drag func
		}
	}

	if (m_clickPoints.size() >= 3)
	{
		AfxMessageBox(_T("3개 이상 만들 수 없습니다!"));
		return;
	}

	PointCircle pc;
	pc.center = point;
	m_clickPoints.push_back(pc);

	int nWidth = m_image.GetWidth();
	int nHeight = m_image.GetHeight();
	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	if (point.x - m_radius < 0 || point.y - m_radius < 0 ||
		point.x + m_radius >= nWidth || point.y + m_radius >= nHeight)
	{
		AfxMessageBox(_T("이미지 영역을 벗어났습니다."));
		return;
	}

	drawCircle(fm, point.x - m_radius, point.y - m_radius, m_radius, 80);

	// draw hollow circle
	if (m_clickPoints.size() == 3)
	{
		makeHollowCircle();
	}
	
	Invalidate(FALSE);

	UpdateClickPointUI();
}

//draging
void CcircleMakerDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_isDragging && (GetAsyncKeyState(VK_LBUTTON) & 0x8000) == 0)
	{
		TRACE("OnMouseMove: Dragging forcibly ended\n");
		m_isDragging = false;
		m_selectedPointIndex = -1;
		ReleaseCapture();
		return;
	}//드래그 강제종료

	if (m_isDragging && m_selectedPointIndex >= 0)
	{
		ULONGLONG currentTime = GetTickCount64();
		if (currentTime - m_lastUpdateTime >= 100) // FIX HERE to change update time
		{
			m_lastUpdateTime = currentTime;

			m_clickPoints[m_selectedPointIndex].center = point;

			int nPitch = m_image.GetPitch();
			int nHeight = m_image.GetHeight();
			unsigned char* fm = (unsigned char*)m_image.GetBits();
			memset(fm, 0xFF, nPitch * nHeight);

			makeHollowCircle();

			Invalidate(FALSE);
			UpdateClickPointUI();
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

//drag end
void CcircleMakerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_isDragging)
	{
		m_isDragging = false;
		m_selectedPointIndex = -1;
		ReleaseCapture();
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}