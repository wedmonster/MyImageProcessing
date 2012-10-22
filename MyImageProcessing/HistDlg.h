#pragma once


// CHistDlg ��ȭ �����Դϴ�.

class CHistDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistDlg)

public:
	CHistDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CHistDlg();
	void SetImage(CxImage* img, int k = 0);
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_HIST_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
