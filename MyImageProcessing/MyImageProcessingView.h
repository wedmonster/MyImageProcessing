
// MyImageProcessingView.h : CMyImageProcessingView Ŭ������ �������̽�
//

#pragma once


class CMyImageProcessingView : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	CMyImageProcessingView();
	DECLARE_DYNCREATE(CMyImageProcessingView)

// Ư���Դϴ�.
public:
	CMyImageProcessingDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CMyImageProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // MyImageProcessingView.cpp�� ����� ����
inline CMyImageProcessingDoc* CMyImageProcessingView::GetDocument() const
   { return reinterpret_cast<CMyImageProcessingDoc*>(m_pDocument); }
#endif

