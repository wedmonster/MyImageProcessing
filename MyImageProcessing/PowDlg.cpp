// PowDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MyImageProcessing.h"
#include "PowDlg.h"
#include "afxdialogex.h"


// CPowDlg ��ȭ �����Դϴ�.

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


// CPowDlg �޽��� ó�����Դϴ�.
