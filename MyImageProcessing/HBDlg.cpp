// HBDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MyImageProcessing.h"
#include "HBDlg.h"
#include "afxdialogex.h"


// CHBDlg ��ȭ �����Դϴ�.

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


// CHBDlg �޽��� ó�����Դϴ�.
