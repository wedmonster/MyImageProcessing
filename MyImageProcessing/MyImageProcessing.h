
// MyImageProcessing.h : MyImageProcessing ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CMyImageProcessingApp:
// �� Ŭ������ ������ ���ؼ��� MyImageProcessing.cpp�� �����Ͻʽÿ�.
//

class CMyImageProcessingApp : public CWinApp
{
public:
	CMyImageProcessingApp();
	CxImage *m_pNewImage;
	MyImage *m_NewImage;

// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyImageProcessingApp theApp;
