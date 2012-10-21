#pragma once


// CSclDlg 대화 상자입니다.

class CSclDlg : public CDialog
{
	DECLARE_DYNAMIC(CSclDlg)

public:
	CSclDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSclDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nType;
	int m_Cx;
	int m_Cy;
};
