// HBDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MyImageProcessing.h"
#include "HBDlg.h"
#include "afxdialogex.h"


// CHBDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHBDlg, CDialogEx)

CHBDlg::CHBDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHBDlg::IDD, pParent)
	, m_A(0)
{

}

CHBDlg::~CHBDlg()
{
}

void CHBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HB_A, m_A);
}


BEGIN_MESSAGE_MAP(CHBDlg, CDialogEx)
END_MESSAGE_MAP()


// CHBDlg 메시지 처리기입니다.
