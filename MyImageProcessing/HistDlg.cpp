// HistDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MyImageProcessing.h"
#include "HistDlg.h"
#include "afxdialogex.h"


// CHistDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CHistDlg, CDialogEx)

CHistDlg::CHistDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHistDlg::IDD, pParent)
{
	
}

CHistDlg::~CHistDlg()
{
}

void CHistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHistDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO1, &CHistDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CHistDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CHistDlg::OnBnClickedRadio3)
END_MESSAGE_MAP()


// CHistDlg �޽��� ó�����Դϴ�.

void CHistDlg::SetImage(CxImage* img, int k)
{
	m_img = img;
	int tmp[256] = {0, };
	memset(m_Histogram, 0.0, sizeof(m_Histogram));
	for(int y = 0; y < img->GetHeight(); y++){
		for(int x = 0; x < img->GetWidth(); x++){
			if(k == 0)	tmp[ img->GetPixelColor(x, y).rgbRed ]++;
			else if(k == 1)	tmp[ img->GetPixelColor(x, y).rgbBlue ]++;
			else if(k == 2)	tmp[ img->GetPixelColor(x, y).rgbGreen ]++;
		}
	}

	double area = img->GetHeight() * img->GetWidth();
	double _max = 0.0;
	for(int i = 0; i < 256; i++){
		m_Histogram[i] = (double) tmp[i] / area;
		_max = max(_max, m_Histogram[i]);
	}

	for(int i = 0; i < 256; i++)
		m_Histogram[i] = (int) (m_Histogram[i]*100/_max);	
}

void CHistDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
	register int i;
	
	dc.MoveTo(20, 30);
	dc.LineTo(20, 130);
	dc.LineTo(275, 130);
	for(i = 0; i < 256; i++)
	{
		dc.MoveTo(20 + i, 130);
		dc.LineTo(20 + i, 130 - m_Histogram[i]);
	}
	for(i = 0; i < 256; i++){
		dc.SelectStockObject(DC_PEN);
		dc.SetDCPenColor(RGB(i, i, i));
		dc.MoveTo(20 + i, 140);
		dc.LineTo(20 + i, 155);
	}
}


void CHistDlg::OnBnClickedRadio1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	SetImage(m_img, 0);
	this->SendMessage(WM_PAINT, 0, 0);
	Invalidate();
}


void CHistDlg::OnBnClickedRadio2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SetImage(m_img, 1);
	this->OnPaint();
	Invalidate();
}


void CHistDlg::OnBnClickedRadio3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SetImage(m_img, 2);
	this->SendMessage(WM_PAINT, 0, 0);
	Invalidate();
}


BOOL CHistDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CButton* pCheck;
	pCheck = (CButton *) GetDlgItem(IDC_RADIO1);
	pCheck->SetCheck(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
