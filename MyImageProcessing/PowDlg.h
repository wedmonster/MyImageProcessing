#pragma once


// CPowDlg ��ȭ �����Դϴ�.

class CPowDlg : public CDialog
{
	DECLARE_DYNAMIC(CPowDlg)

public:
	CPowDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPowDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_POW_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	double m_t;
};
