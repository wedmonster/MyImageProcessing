
// MyImageProcessingDoc.cpp : CMyImageProcessingDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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


// CMyImageProcessingDoc 생성/소멸

CMyImageProcessingDoc::CMyImageProcessingDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_pImage = NULL;
}

CMyImageProcessingDoc::~CMyImageProcessingDoc()
{
}

BOOL CMyImageProcessingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
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
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMyImageProcessingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
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

// 검색 처리기를 지원합니다.
void CMyImageProcessingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// CMyImageProcessingDoc 진단

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


// CMyImageProcessingDoc 명령


//void CMyImageProcessingDoc::OnFileOpen()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	//m_pImage = new CxImage;
	//m_pImage->Load(lpszPathName);
	m_Image = new MyImage();
	m_Image->Load(lpszPathName);
	
	return TRUE;
}


void CMyImageProcessingDoc::DeleteContents()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	if(m_Image) delete m_Image;

	CDocument::DeleteContents();
}


BOOL CMyImageProcessingDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//return CDocument::OnSaveDocument(lpszPathName);
	return m_pImage->Save(lpszPathName, CXIMAGE_FORMAT_JPG);
}


void CMyImageProcessingDoc::OnImgGray()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ViewImage(m_Image->GrayScaleImage());
}



void CMyImageProcessingDoc::OnImgInv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	

	ViewImage(m_Image->InverseImage());
}


void CMyImageProcessingDoc::OnImgBin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CBinthSet dlg;

	if(dlg.DoModal() == IDOK)
		ViewImage(m_Image->BinarizeImage(dlg.m_binth));
}


void CMyImageProcessingDoc::OnImgScl()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CHistDlg dlg;
	dlg.SetImage(m_Image->GetCxImage());
	if(dlg.DoModal() == IDOK)
	{

	}
}


void CMyImageProcessingDoc::OnHistEq()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ViewImage(m_Image->HistogramEqualizeImage());
}

void CMyImageProcessingDoc::OnLaplacion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ViewImage(m_Image->LaplacianFilterImage());
}


void CMyImageProcessingDoc::OnHighBoost()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CHBDlg dlg;
	if(dlg.DoModal() == IDOK)
		ViewImage(m_Image->HighBoostFilterImage(dlg.m_A));
}


void CMyImageProcessingDoc::OnSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	
	ViewImage(m_Image->SobelFilterImage());
}


void CMyImageProcessingDoc::OnSmLin()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	ViewImage(m_Image->SmoothingLinearFilterImage());
}


void CMyImageProcessingDoc::OnOrderMaxfilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ViewImage(m_Image->MaxFilterImage());
}


void CMyImageProcessingDoc::OnOrderMedianfilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ViewImage(m_Image->MedianFilterImage());
}


void CMyImageProcessingDoc::OnOrderMinfilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ViewImage(m_Image->TransformIntoPolar());
}


void CMyImageProcessingDoc::OnCartesianTrans()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ViewImage(m_Image->TransformIntoCartecian());
}


void CMyImageProcessingDoc::OnPower()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPowDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		ViewImage(m_Image->PowerLawImage(dlg.m_t));
	}
}


void CMyImageProcessingDoc::OnOrderMeanfilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	ViewImage(m_Image->MeanFilterImage());
}


void CMyImageProcessingDoc::OnFft()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	MyImage mImage, pImage;

	m_Image->FFT(mImage, pImage);
	ViewImage(mImage);
	ViewImage(pImage);
}


void CMyImageProcessingDoc::OnDft()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	MyImage mImage, pImage;
	m_Image->DFT(mImage, pImage);
	ViewImage(mImage);
	ViewImage(pImage);
}
