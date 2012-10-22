#pragma once


// CHBDlg 대화 상자입니다.

class CHBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHBDlg)

public:
	CHBDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CHBDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HB_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	double m_A;
};
