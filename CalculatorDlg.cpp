
// CalculatorDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCalculatorDlg 대화 상자



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CALCULATOR_DIALOG, pParent)
	, m_strLCD(_T("0"))
	, m_prevLCD(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strLCD);
	DDX_Text(pDX, IDC_PREV_LCD, m_prevLCD);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_0, &CCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_1, &CCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_NON, &CCalculatorDlg::OnBnClickedButtonNon)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_RST, &CCalculatorDlg::OnBnClickedButtonRst)
	ON_BN_CLICKED(IDC_BUTTON_MiNUS, &CCalculatorDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MUL, &CCalculatorDlg::OnBnClickedButtonMul)
	ON_BN_CLICKED(IDC_BUTTON_DIV, &CCalculatorDlg::OnBnClickedButtonDiv)
END_MESSAGE_MAP()


// CCalculatorDlg 메시지 처리기

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_prevNum = _T("0");
	m_nowNum = _T("0");
	m_Num = 0;
	m_bNewNum = TRUE;
	m_bpNewNum = FALSE;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCalculatorDlg::AddNumber(const LPCTSTR inputNum) {
	UpdateData();

	if ((!m_bNewNum) & (m_strLCD != _T("0"))) {
		m_strLCD = m_strLCD + inputNum;
	}
	else {
		m_strLCD = inputNum;
	}
	if (m_bpNewNum)
		m_prevLCD = _T("");
	
	m_bNewNum = FALSE;
	m_bpNewNum = FALSE;

	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedButton0()
{
	AddNumber(_T("0"));

}


void CCalculatorDlg::OnBnClickedButton1()
{
	AddNumber(_T("1"));
}


void CCalculatorDlg::OnBnClickedButton2()
{
	AddNumber(_T("2"));
}


void CCalculatorDlg::OnBnClickedButton3()
{
	AddNumber(_T("3"));
}


void CCalculatorDlg::OnBnClickedButton4()
{
	AddNumber(_T("4"));
}


void CCalculatorDlg::OnBnClickedButton5()
{
	AddNumber(_T("5"));
}


void CCalculatorDlg::OnBnClickedButton6()
{
	AddNumber(_T("6"));}


void CCalculatorDlg::OnBnClickedButton7()
{
	AddNumber(_T("7"));
}


void CCalculatorDlg::OnBnClickedButton8()
{
	AddNumber(_T("8"));
}


void CCalculatorDlg::OnBnClickedButton9()
{
	AddNumber(_T("9"));
}


void CCalculatorDlg::OnBnClickedButtonNon()
{
	UpdateData();
	m_strLCD = _T("0");
	m_nowNum = _T("0");
	m_prevNum = _T("0");
	m_prevLCD = _T("");

	UpdateData(FALSE);
}

void CCalculatorDlg::Culcase() {

	m_nowNum = m_strLCD;
	switch (m_prevCal)
	{
	case 0: // 이전에 연산자가 없는 경우
		m_Num = _ttoi(m_nowNum.GetBuffer());
		break;

	case 1: // plus
		m_Num = _ttoi(m_prevNum.GetBuffer()) + _ttoi(m_nowNum.GetBuffer());
		break;
	case 2: // minum
		m_Num = _ttoi(m_prevNum.GetBuffer()) - _ttoi(m_nowNum.GetBuffer());
		break;
	case 3: // mul
		m_Num = _ttoi(m_prevNum.GetBuffer()) * _ttoi(m_nowNum.GetBuffer());
		break;
	case 4: // div
		m_Num = _ttoi(m_prevNum.GetBuffer()) / _ttoi(m_nowNum.GetBuffer());
		break;
	}
	m_strLCD.Format(_T("%d"), m_Num);
}
void CCalculatorDlg::Culoper(LPCTSTR inputOper) {

	UpdateData();
	m_prevLCD += m_strLCD;

	if (m_prevNum == _T("0")) {
		m_prevNum = m_strLCD; // LCD 값 변수에 대입
	}
	else {
		Culcase();
		m_prevNum.Format(_T("%d"), m_Num);
	}
	m_bNewNum = TRUE;
	m_prevLCD += inputOper;
	UpdateData(FALSE);
}

void CCalculatorDlg::OnBnClickedButtonPlus()
{
	Culoper(_T(" + "));
	m_prevCal = 1;
}
void CCalculatorDlg::OnBnClickedButtonMinus()
{
	Culoper(_T(" - "));
	m_prevCal = 2;
}
void CCalculatorDlg::OnBnClickedButtonMul()
{
	Culoper(_T(" * "));
	m_prevCal = 3;
}
void CCalculatorDlg::OnBnClickedButtonDiv()
{
	Culoper(_T(" / "));
	m_prevCal = 4;
}

void CCalculatorDlg::OnBnClickedButtonRst()
{
	UpdateData();
	if (m_bpNewNum)
		m_prevLCD = _T("");

	m_prevLCD += m_strLCD;

	Culcase();

	m_prevCal = 0;

	m_nowNum = _T("0");
	m_prevNum = _T("0");
	m_bNewNum = TRUE;
	m_bpNewNum = TRUE;

	UpdateData(FALSE);
}
