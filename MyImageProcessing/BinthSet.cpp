// BinthSet.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MyImageProcessing.h"
#include "BinthSet.h"
#include "afxdialogex.h"


// CBinthSet 대화 상자입니다.

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


// CBinthSet 메시지 처리기입니다.


void CBinthSet::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnOK();
}
