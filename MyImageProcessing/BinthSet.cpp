// BinthSet.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MyImageProcessing.h"
#include "BinthSet.h"
#include "afxdialogex.h"


// CBinthSet ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CBinthSet, CDialog)

CBinthSet::CBinthSet(CWnd* pParent /*=NULL*/)
	: CDialog(CBinthSet::IDD, pParent)
	, m_binth(0)
{

}

CBinthSet::~CBinthSet()
{
}

void CBinthSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BINTHRE, m_binth);
	DDV_MinMaxInt(pDX, m_binth, 0, 255);
}


BEGIN_MESSAGE_MAP(CBinthSet, CDialog)
	ON_BN_CLICKED(IDOK, &CBinthSet::OnBnClickedOk)
END_MESSAGE_MAP()


// CBinthSet �޽��� ó�����Դϴ�.


void CBinthSet::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialog::OnOK();
}
