
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
#include "SclDlg.h"
#include "function.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "HistDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyImageProcessingDoc

IMPLEMENT_DYNCREATE(CMyImageProcessingDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyImageProcessingDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CMyImageProcessingDoc::OnFileOpen)
	ON_COMMAND(ID_IMG_GRAY, &CMyImageProcessingDoc::OnImgGray)
	ON_COMMAND(ID_IMG_INV, &CMyImageProcessingDoc::OnImgInv)
	ON_COMMAND(ID_IMG_BIN, &CMyImageProcessingDoc::OnImgBin)
	ON_COMMAND(ID_IMG_SCL, &CMyImageProcessingDoc::OnImgScl)
	ON_COMMAND(ID_HIST, &CMyImageProcessingDoc::OnHist)
	ON_COMMAND(ID_HIST_EQ, &CMyImageProcessingDoc::OnHistEq)
	ON_COMMAND(ID_LAPLACION, &CMyImageProcessingDoc::OnLaplacion)
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


void CMyImageProcessingDoc::OnFileOpen()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	char szFilter[]="Image files | \*.bmp;*.gif;*.jpg;*.jpeg;*.png;*.ico;*.tif;*.tiff;*.tga;*.pcx;\All Files(*.*)|*.*||";
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
	if(IDOK == fileDlg.DoModal())
		OnOpenDocument(fileDlg.GetPathName());

}


BOOL CMyImageProcessingDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_pImage = new CxImage;
	m_pImage->Load(lpszPathName);

	return TRUE;
}


void CMyImageProcessingDoc::DeleteContents()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(m_pImage) delete m_pImage;

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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	RGBQUAD color;
	int gray;
	for(int y = 0; y < m_pImage->GetHeight(); y++){
		for(int x = 0; x < m_pImage->GetWidth(); x++){
			color = m_pImage->GetPixelColor(x, y);
			gray = (color.rgbRed + color.rgbGreen + color.rgbBlue) / 3;
			m_pImage->SetPixelColor(x, y, RGB(gray, gray, gray)); 
		}
		UpdateAllViews(NULL);
	}
}



void CMyImageProcessingDoc::OnImgInv()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	RGBQUAD color;
	int r, g, b;
	for(int y = 0; y < m_pImage->GetHeight(); y++){
		for(int x = 0; x < m_pImage->GetWidth(); x++){
			color = m_pImage->GetPixelColor(x, y);
			r = 0xff ^ color.rgbRed;
			g = 0xff ^ color.rgbGreen;
			b = 0xff ^ color.rgbBlue;

			m_pImage->SetPixelColor(x, y, RGB(r, g, b));
		}
	}

	UpdateAllViews(NULL);
}


void CMyImageProcessingDoc::OnImgBin()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	int x, y;
	int gray, threshold;

	CBinthSet dlg;

	if(dlg.DoModal() == IDOK)
	{
		CxImage tmp;
		tmp.Copy(*m_pImage);

		threshold = dlg.m_binth;

		for(int y = 0; y < m_pImage->GetHeight(); y++){
			for(int x = 0; x < m_pImage->GetWidth(); x++){
				gray = m_pImage->GetPixelGray(x, y);
				if(gray > threshold) gray = 255;
				else gray = 0;

				tmp.SetPixelColor(x, y, RGB(gray, gray, gray));
			}
		}
		m_pImage->Copy(tmp);
	}
	UpdateAllViews(NULL);
}


void CMyImageProcessingDoc::OnImgScl()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	//int Cx = 10;
	//int Cy = 10;

	//CxImage tmp;
	//tmp.Create(Cx*m_pImage->GetWidth(), Cy*m_pImage->GetHeight(), m_pImage->GetBpp());
	////tmp.Copy(*m_pImage);
	//for(int w = 0; w < m_pImage->GetHeight(); w++){
	//	for(int v = 0; v < m_pImage->GetWidth(); v++){
	//		int x = Cx*v;
	//		int y = Cy*w;
	//		tmp.SetPixelColor(x, y, m_pImage->GetPixelColor(v, w));
	//	}
	//}
	//m_pImage->Copy(tmp);
	//UpdateAllViews(NULL);
	CSclDlg dlg;

	if(dlg.DoModal() == IDOK){
		int type = dlg.m_nType;
		double Cx = 0.0;
		double Cy = 0.0;
		RGBQUAD rgb;
		if(type == 1){
			//zoom
			Cx = (double)dlg.m_Cx;
			Cy = (double)dlg.m_Cy;
		}else{
			//shrink
			Cx = 1.0 / (double) dlg.m_Cx;
			Cy = 1.0 / (double) dlg.m_Cy;
		}

		CxImage tmp;
		tmp.Create(Cx*m_pImage->GetWidth(), Cy*m_pImage->GetHeight(), m_pImage->GetBpp());
		MATRIX3D inv = ScaleT_Matrix(Cx, Cy);
		for(int y = 0; y < tmp.GetHeight(); y++) {
			for(int x = 0; x < tmp.GetWidth(); x++) {
				tmp.SetPixelColor( x, y, BilinearInterpolation( ScaleT( _POINT(x, y), inv ), *m_pImage ) );
				//tmp.SetPixelColor( x, y, NoInterpolation( ScaleT( _POINT(x, y), inv ), *m_pImage ) );
				//tmp.SetPixelColor( x, y, NearestNeihborInterpolation( ScaleT( _POINT(x, y), inv ), *m_pImage ) );
			}
		}
		
		m_pImage->Copy(tmp);
		UpdateAllViews(NULL);

		CMainFrame *pFrame = (CMainFrame*) AfxGetMainWnd();
		CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();		
		CMyImageProcessingView *pView = (CMyImageProcessingView*) pChild->GetActiveView();
		pView->SendMessage(WM_INITIALUPDATE, 0, 0);

		

	}

}


void CMyImageProcessingDoc::OnHist()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CHistDlg dlg;
	dlg.SetImage(m_pImage);
	if(dlg.DoModal() == IDOK)
	{

	}
}


void CMyImageProcessingDoc::OnHistEq()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	int cdf[256][3] = {0, };
	int n[256][3] = {0,};
	int s[256][3] = {0, };	
	
	for(int y = 0; y < m_pImage->GetHeight(); y++){
		for(int x = 0; x < m_pImage->GetWidth(); x++){
			n[ m_pImage->GetPixelColor(x, y).rgbRed ][R]++;		
			n[ m_pImage->GetPixelColor(x, y).rgbGreen ][G]++;
			n[ m_pImage->GetPixelColor(x, y).rgbBlue ][B]++;
		}
	}
	cdf[0][R] = n[0][R];
	cdf[0][G] = n[0][G];
	cdf[0][B] = n[0][B];

	for(int i = 1; i < 256; i++){
		cdf[i][R] = cdf[i-1][R] + n[i][R];
		cdf[i][G] = cdf[i-1][G] + n[i][G];
		cdf[i][B] = cdf[i-1][B] + n[i][B];
	}

	double MN = m_pImage->GetWidth() * m_pImage->GetHeight();
	int L = 256;

	for(int i = 0; i < 256; i++){
		s[i][R] = ROUND((double)(L - 1)/MN*cdf[i][R]);
		s[i][G] = ROUND((double)(L - 1)/MN*cdf[i][G]);
		s[i][B] = ROUND((double)(L - 1)/MN*cdf[i][B]);
	}

	CxImage tmp;
	tmp.Copy(*m_pImage);
	for(int y = 0; y < tmp.GetHeight(); y++){
		for(int x = 0; x < tmp.GetWidth(); x++){
			int red = m_pImage->GetPixelColor(x, y).rgbRed;
			int green = m_pImage->GetPixelColor(x, y).rgbGreen;
			int blue = m_pImage->GetPixelColor(x, y).rgbBlue;
			tmp.SetPixelColor(x, y, RGB(s[red][R], s[green][G], s[blue][B]));
		}
	}
	m_pImage->Copy(tmp);
	UpdateAllViews(NULL);
}

int CMyImageProcessingDoc::calcMask(double mask[][3], int x, int y, int k){
	double sum = 0.0;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(k == R)
				sum += (mask[i][j] * m_pImage->GetPixelColor(x-1+i, y-1+j).rgbRed);
			else if(k == G)
				sum += (mask[i][j] * m_pImage->GetPixelColor(x-1+i, y-1+j).rgbGreen);
			else if(k == B)
				sum += (mask[i][j] * m_pImage->GetPixelColor(x-1+i, y-1+j).rgbBlue);
		}
	}
	if(sum > 255.0) return 255;
	else if(sum < 0) return 0;
	
	return (int) sum;
}


void CMyImageProcessingDoc::OnLaplacion()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	double mask[3][3] = {-1, -1, -1,
						 -1, 9, -1,
						 -1, -1, -1};
	CxImage tmp;
	tmp.Copy(*m_pImage);
	for(int y = 1; y < m_pImage->GetHeight()-1; y++){
		for(int x = 1; x < m_pImage->GetWidth()-1; x++){
			int red = calcMask(mask, x, y, R);
			int green = calcMask(mask, x, y, G);
			int blue = calcMask(mask, x, y, B);
			
			

			tmp.SetPixelColor(x, y, RGB(red, green, blue));
		}
	}
	m_pImage->Copy(tmp);
	UpdateAllViews(NULL);
}
