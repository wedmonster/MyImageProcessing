#pragma once


// CSclDlg ��ȭ �����Դϴ�.

class CSclDlg : public CDialog
{
	DECLARE_DYNAMIC(CSclDlg)

public:
	CSclDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSclDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_nType;
	int m_Cx;
	int m_Cy;
};
