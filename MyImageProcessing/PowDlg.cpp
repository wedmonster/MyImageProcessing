// PowDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MyImageProcessing.h"
#include "PowDlg.h"
#include "afxdialogex.h"


// CPowDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CPowDlg, CDialog)

CPowDlg::CPowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPowDlg::IDD, pParent)
	, m_t(0)
{

}

CPowDlg::~CPowDlg()
{
}

void CPowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_T, m_t);
}


BEGIN_MESSAGE_MAP(CPowDlg, CDialog)
END_MESSAGE_MAP()


// CPowDlg 메시지 처리기입니다.
