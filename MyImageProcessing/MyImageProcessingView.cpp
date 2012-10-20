
// MyImageProcessingView.cpp : CMyImageProcessingView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "MyImageProcessing.h"
#endif

#include "MyImageProcessingDoc.h"
#include "MyImageProcessingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyImageProcessingView

IMPLEMENT_DYNCREATE(CMyImageProcessingView, CScrollView)

BEGIN_MESSAGE_MAP(CMyImageProcessingView, CScrollView)
END_MESSAGE_MAP()

// CMyImageProcessingView ����/�Ҹ�

CMyImageProcessingView::CMyImageProcessingView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CMyImageProcessingView::~CMyImageProcessingView()
{
}

BOOL CMyImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CMyImageProcessingView �׸���

void CMyImageProcessingView::OnDraw(CDC* pDC)
{
	CMyImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	
	if (pDoc->m_pImage)
		pDoc->m_pImage->Draw(pDC->GetSafeHdc(), CRect(0,0,(int)(pDoc->m_pImage->GetWidth()),(int)(pDoc->m_pImage->GetHeight())));


}

void CMyImageProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �� ���� ��ü ũ�⸦ ����մϴ�.
	CMyImageProcessingDoc *pDoc = GetDocument();
	if(pDoc->m_pImage)
		sizeTotal = CSize(pDoc->m_pImage->GetWidth(), pDoc->m_pImage->GetHeight());

	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMyImageProcessingView ����

#ifdef _DEBUG
void CMyImageProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMyImageProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMyImageProcessingDoc* CMyImageProcessingView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyImageProcessingDoc)));
	return (CMyImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyImageProcessingView �޽��� ó����
