#pragma once


// CHBDlg ��ȭ �����Դϴ�.

class CHBDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHBDlg)

public:
	CHBDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CHBDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_HB_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	double m_A;
};
