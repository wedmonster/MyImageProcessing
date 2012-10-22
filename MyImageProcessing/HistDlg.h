#pragma once


// CHistDlg 대화 상자입니다.

class CHistDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistDlg)

public:
	CHistDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CHistDlg();
	void SetImage(CxImage* img, int k = 0);
// 대화 상자 데이터입니다.
	enum { IDD = IDD_HIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
private:
	double m_Histogram[256];
	CxImage* m_img;
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	virtual BOOL OnInitDialog();
};
