
// MyImageProcessingView.cpp : CMyImageProcessingView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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

// CMyImageProcessingView 생성/소멸

CMyImageProcessingView::CMyImageProcessingView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMyImageProcessingView::~CMyImageProcessingView()
{
}

BOOL CMyImageProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMyImageProcessingView 그리기

void CMyImageProcessingView::OnDraw(CDC* /*pDC*/)
{
	CMyImageProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}

void CMyImageProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMyImageProcessingView 진단

#ifdef _DEBUG
void CMyImageProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMyImageProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMyImageProcessingDoc* CMyImageProcessingView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyImageProcessingDoc)));
	return (CMyImageProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyImageProcessingView 메시지 처리기
