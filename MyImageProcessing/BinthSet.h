#pragma once


// CBinthSet ��ȭ �����Դϴ�.

class CBinthSet : public CDialog
{
	DECLARE_DYNAMIC(CBinthSet)

public:
	CBinthSet(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBinthSet();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_BIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	int m_binth;
	afx_msg void OnBnClickedOk();
};
