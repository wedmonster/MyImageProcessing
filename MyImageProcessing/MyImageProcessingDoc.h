
// MyImageProcessingDoc.h : CMyImageProcessingDoc Ŭ������ �������̽�
//


#pragma once


class CMyImageProcessingDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CMyImageProcessingDoc();
	DECLARE_DYNCREATE(CMyImageProcessingDoc)

// Ư���Դϴ�.
public:
	CxImage* m_pImage;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CMyImageProcessingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileOpen();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	afx_msg void OnImgGray();
	afx_msg void OnImgInv();
	afx_msg void OnImgBin();
	afx_msg void OnImgScl();
	afx_msg void OnHist();
};
