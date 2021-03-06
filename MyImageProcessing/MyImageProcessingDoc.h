
// MyImageProcessingDoc.h : CMyImageProcessingDoc 클래스의 인터페이스
//


#pragma once


class CMyImageProcessingDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMyImageProcessingDoc();
	DECLARE_DYNCREATE(CMyImageProcessingDoc)

// 특성입니다.
public:
	CxImage* m_pImage;
	MyImage* m_Image;
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMyImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
//	afx_msg void OnFileOpen();
	void ViewImage(MyImage& img);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnImgGray();
	afx_msg void OnImgInv();
	afx_msg void OnImgBin();
	afx_msg void OnImgScl();
	afx_msg void OnHist();
	afx_msg void OnHistEq();
	afx_msg void OnLaplacion();
	int calcMask(double mask[][3], int x, int y, int k);
	afx_msg void OnHighBoost();
	afx_msg void OnSobel();
	afx_msg void OnSmLin();
	afx_msg void OnOrderMaxfilter();
	afx_msg void OnOrderMedianfilter();
	afx_msg void OnOrderMinfilter();
//	afx_msg void OnFileNewOpen();
	afx_msg void OnPolarTrans();
	afx_msg void OnPolarTransInv();
	afx_msg void OnCartesianTrans();
	afx_msg void OnPower();
	afx_msg void OnOrderMeanfilter();
	afx_msg void OnFft();
	afx_msg void OnDft();
};
