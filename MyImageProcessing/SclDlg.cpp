// SclDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MyImageProcessing.h"
#include "SclDlg.h"
#include "afxdialogex.h"


// CSclDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSclDlg, CDialog)

CSclDlg::CSclDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSclDlg::IDD, pParent)
	, m_nType(0)
	, m_Cx(0)
	, m_Cy(0)
{

}

CSclDlg::~CSclDlg()
{
}

void CSclDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_TYPE, m_nType);
	DDX_Text(pDX, IDC_EDIT_SCL_WIDTH, m_Cx);
	DDX_Text(pDX, IDC_EDIT_SCL_HEIGHT, m_Cy);
}


BEGIN_MESSAGE_MAP(CSclDlg, CDialog)
END_MESSAGE_MAP()


// CSclDlg 메시지 처리기입니다.
