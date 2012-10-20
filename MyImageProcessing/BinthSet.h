#pragma once


// CBinthSet 대화 상자입니다.

class CBinthSet : public CDialog
{
	DECLARE_DYNAMIC(CBinthSet)

public:
	CBinthSet(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBinthSet();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_BIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_binth;
	afx_msg void OnBnClickedOk();
};
