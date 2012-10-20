
// MyImageProcessingView.h : CMyImageProcessingView 클래스의 인터페이스
//

#pragma once


class CMyImageProcessingView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CMyImageProcessingView();
	DECLARE_DYNCREATE(CMyImageProcessingView)

// 특성입니다.
public:
	CMyImageProcessingDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CMyImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // MyImageProcessingView.cpp의 디버그 버전
inline CMyImageProcessingDoc* CMyImageProcessingView::GetDocument() const
   { return reinterpret_cast<CMyImageProcessingDoc*>(m_pDocument); }
#endif

