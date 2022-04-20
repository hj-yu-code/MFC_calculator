
// CalculatorDlg.h: 헤더 파일
//

#pragma once


// CCalculatorDlg 대화 상자
class CCalculatorDlg : public CDialog
{
// 생성입니다.
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	bool m_bNewNum;
	bool m_bpNewNum;
	void AddNumber(LPCTSTR inputNum);
	void Culcase();
	void Culoper(LPCTSTR inputOper);


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strLCD;
	int m_prevCal;
	CString m_prevNum;
	CString m_nowNum;
	int m_Num;
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonNon();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonRst();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonMul();
	afx_msg void OnBnClickedButtonDiv();
	CString m_prevLCD;
};
