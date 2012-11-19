
// MyImageProcessingDoc.cpp : CMyImageProcessingDoc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MyImageProcessing.h"
#endif

#include "MyImageProcessingDoc.h"
#include "MyImageProcessingView.h"
#include "BinthSet.h"
#include "PowDlg.h"
#include "SclDlg.h"
//#include "function.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "HistDlg.h"
#include "HBDlg.h"
#include <propkey.h>
#include <cmath>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyImageProcessingDoc

IMPLEMENT_DYNCREATE(CMyImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyImageProcessingDoc, CDocument)
//	ON_COMMAND(ID_FILE_OPEN, &CMyImageProcessingDoc::OnFileOpen)
	ON_COMMAND(ID_IMG_GRAY, &CMyImageProcessingDoc::OnImgGray)
	ON_COMMAND(ID_IMG_INV, &CMyImageProcessingDoc::OnImgInv)
	ON_COMMAND(ID_IMG_BIN, &CMyImageProcessingDoc::OnImgBin)
	ON_COMMAND(ID_IMG_SCL, &CMyImageProcessingDoc::OnImgScl)
	ON_COMMAND(ID_HIST, &CMyImageProcessingDoc::OnHist)
	ON_COMMAND(ID_HIST_EQ, &CMyImageProcessingDoc::OnHistEq)
	ON_COMMAND(ID_LAPLACION, &CMyImageProcessingDoc::OnLaplacion)
	ON_COMMAND(ID_HIGH_BOOST, &CMyImageProcessingDoc::OnHighBoost)
	ON_COMMAND(ID_SOBEL, &CMyImageProcessingDoc::OnSobel)
	ON_COMMAND(ID_SM_LIN, &CMyImageProcessingDoc::OnSmLin)
	ON_COMMAND(ID_ORDER_MAXFILTER, &CMyImageProcessingDoc::OnOrderMaxfilter)
	ON_COMMAND(ID_ORDER_MEDIANFILTER, &CMyImageProcessingDoc::OnOrderMedianfilter)
	ON_COMMAND(ID_ORDER_MINFILTER, &CMyImageProcessingDoc::OnOrderMinfilter)
//	ON_COMMAND(ID_FILE_NEW_OPEN, &CMyImageProcessingDoc::OnFileNewOpen)
ON_COMMAND(ID_POLAR_TRANS, &CMyImageProcessingDoc::OnPolarTrans)
ON_COMMAND(ID_POLAR_TRANS_INV, &CMyImageProcessingDoc::OnPolarTransInv)
ON_COMMAND(ID_CARTESIAN_TRANS, &CMyImageProcessingDoc::OnCartesianTrans)
ON_COMMAND(ID_POWER, &CMyImageProcessingDoc::OnPower)
ON_COMMAND(ID_ORDER_MEANFILTER, &CMyImageProcessingDoc::OnOrderMeanfilter)
ON_COMMAND(ID_FFT, &CMyImageProcessingDoc::OnFft)
ON_COMMAND(ID_DFT, &CMyImageProcessingDoc::OnDft)
END_MESSAGE_MAP()


// CMyImageProcessingDoc ����/�Ҹ�

CMyImageProcessingDoc::CMyImageProcessingDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
	m_pImage = NULL;
}

CMyImageProcessingDoc::~CMyImageProcessingDoc()
{
}

BOOL CMyImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.
	//m_pImage = new CxImage;
	//m_pImage->Copy(*theApp.m_pNewImage);
	m_Image = new MyImage(*theApp.m_NewImage);

	return TRUE;
}




// CMyImageProcessingDoc serialization

void CMyImageProcessingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CMyImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CMyImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMyImageProcessingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyImageProcessingDoc ����

#ifdef _DEBUG
void CMyImageProcessingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyImageProcessingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyImageProcessingDoc ���


//void CMyImageProcessingDoc::OnFileOpen()
//{
//	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
///*	char szFilter[]="Image files | \*.bmp;*.gif;*.jpg;*.jpeg;*.png;*.ico;*.tif;*.tiff;*.tga;*.pcx;\All Files(*.*)|*.*||";
//	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
//	if(IDOK == fileDlg.DoModal())
//		OnOpenDocument(fileDlg.GetPathName());*/
//		
//}


BOOL CMyImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	//m_pImage = new CxImage;
	//m_pImage->Load(lpszPathName);
	m_Image = new MyImage();
	m_Image->Load(lpszPathName);
	
	return TRUE;
}


void CMyImageProcessingDoc::DeleteContents()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
//	if(m_Image) delete m_Image;

	CDocument::DeleteContents();
}


BOOL CMyImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	//return CDocument::OnSaveDocument(lpszPathName);
	return m_pImage->Save(lpszPathName, CXIMAGE_FORMAT_JPG);
}


void CMyImageProcessingDoc::OnImgGray()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ViewImage(m_Image->GrayScaleImage());
}



void CMyImageProcessingDoc::OnImgInv()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	

	ViewImage(m_Image->InverseImage());
}


void CMyImageProcessingDoc::OnImgBin()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CBinthSet dlg;

	if(dlg.DoModal() == IDOK)
		ViewImage(m_Image->BinarizeImage(dlg.m_binth));
}


void CMyImageProcessingDoc::OnImgScl()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CSclDlg dlg;

	if(dlg.DoModal() == IDOK){
		int type = dlg.m_nType;
		double Cx = 0.0;
		double Cy = 0.0;

		if(type == 1){
			//zoom
			Cx = (double)dlg.m_Cx;
			Cy = (double)dlg.m_Cy;
		}else{
			//shrink
			Cx = 1.0 / (double) dlg.m_Cx;
			Cy = 1.0 / (double) dlg.m_Cy;
		}
		
		ViewImage(m_Image->ScaleImage(Cx, Cy));

		/*
		CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();
		CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();		
		CMyImageProcessingView *pView = (CMyImageProcessingView*) pChild->GetActiveView();
		pView->SendMessage(WM_INITIALUPDATE, 0, 0);*/
	}

}


void CMyImageProcessingDoc::OnHist()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CHistDlg dlg;
	dlg.SetImage(m_Image->GetCxImage());
	if(dlg.DoModal() == IDOK)
	{

	}
}


void CMyImageProcessingDoc::OnHistEq()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ViewImage(m_Image->HistogramEqualizeImage());
}

void CMyImageProcessingDoc::OnLaplacion()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ViewImage(m_Image->LaplacianFilterImage());
}


void CMyImageProcessingDoc::OnHighBoost()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CHBDlg dlg;
	if(dlg.DoModal() == IDOK)
		ViewImage(m_Image->HighBoostFilterImage(dlg.m_A));
}


void CMyImageProcessingDoc::OnSobel()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	
	ViewImage(m_Image->SobelFilterImage());
}


void CMyImageProcessingDoc::OnSmLin()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

	ViewImage(m_Image->SmoothingLinearFilterImage());
}


void CMyImageProcessingDoc::OnOrderMaxfilter()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ViewImage(m_Image->MaxFilterImage());
}


void CMyImageProcessingDoc::OnOrderMedianfilter()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ViewImage(m_Image->MedianFilterImage());
}


void CMyImageProcessingDoc::OnOrderMinfilter()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ViewImage(m_Image->MinFilterImage());
}

void CMyImageProcessingDoc::ViewImage(MyImage& img)
{
	//theApp.m_pNewImage = &img;
	theApp.m_NewImage = &img;
	AfxGetMainWnd()->SendMessage(WM_COMMAND, ID_FILE_NEW);

}


void CMyImageProcessingDoc::OnPolarTrans()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CxImage tmp;
	//tmp.Copy(*m_pImage);
		
	int c_x = m_pImage->GetWidth() / 2;
	int c_y = m_pImage->GetHeight() / 2;

	tmp.Create(360, sqrt( pow( c_x, 2.0) + pow(c_y, 2.0) ), m_pImage->GetBpp());

	for(int y = 0; y < m_pImage->GetHeight(); y++){
		for(int x = 0; x < m_pImage->GetWidth(); x++){
			double r = sqrt( pow( c_x - x , 2.0) + pow(c_y - y, 2.0) );
			double theta = 0.0;
			if(c_x - x != 0){				
				if(c_y - y == 0.0){
					if(c_y < y) theta = 270.0;
					else theta = 90.0;
				}else{
					double m = (double)(y - c_y) /(double)(x - c_x);
					theta = atan(m)*180/M_PI;
					if(x - c_x < 0) theta += 180;
					else if(y - c_y < 0) theta += 360;
				}
			}else{
				if(c_x <= x) theta = 0.0;
				else theta = 180.0;
			}
			//theta*=2;
			tmp.SetPixelColor((int) (theta + 0.5), (int) (r+0.5), m_pImage->GetPixelColor(x, y));
		}
	}

//	ViewImage(tmp);
}


void CMyImageProcessingDoc::OnPolarTransInv()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ViewImage(m_Image->TransformIntoPolar());
}


void CMyImageProcessingDoc::OnCartesianTrans()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ViewImage(m_Image->TransformIntoCartecian());
}


void CMyImageProcessingDoc::OnPower()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CPowDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		ViewImage(m_Image->PowerLawImage(dlg.m_t));
	}
}


void CMyImageProcessingDoc::OnOrderMeanfilter()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	ViewImage(m_Image->MeanFilterImage());
}


void CMyImageProcessingDoc::OnFft()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	MyImage mImage, pImage;

	m_Image->FFT(mImage, pImage);
	ViewImage(mImage);
	ViewImage(pImage);
}


void CMyImageProcessingDoc::OnDft()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	MyImage mImage, pImage;
	m_Image->DFT(mImage, pImage);
	ViewImage(mImage);
	ViewImage(pImage);
}
