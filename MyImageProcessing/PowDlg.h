#pragma once


// CPowDlg 대화 상자입니다.

class CPowDlg : public CDialog
{
	DECLARE_DYNAMIC(CPowDlg)

public:
	CPowDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPowDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_POW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_t;
};
