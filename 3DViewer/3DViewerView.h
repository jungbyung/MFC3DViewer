
// 3DViewerView.h : CMy3DViewerView Ŭ������ �������̽�
//

#pragma once
#include "cMain.h"

class CMy3DViewerView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMy3DViewerView();
	DECLARE_DYNCREATE(CMy3DViewerView)

// Ư���Դϴ�.
public:
	CMy3DViewerDoc* GetDocument() const;

// �۾��Դϴ�.
public:
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CMy3DViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	cMain* m_pMain;
	CDC m_memDC;
	CBitmap* m_pOldBitmap;
	CBitmap m_bmp;
// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
//	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnInitialUpdate();
	virtual BOOL DestroyWindow();
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void On32775();
	afx_msg void On32776();
	afx_msg void On32777();
	afx_msg void On32778();
	afx_msg void Ontest();
	afx_msg void Onloadobj();
	afx_msg void On32780();
	afx_msg void On32781();
	afx_msg void On32782();
};

#ifndef _DEBUG  // 3DViewerView.cpp�� ����� ����
inline CMy3DViewerDoc* CMy3DViewerView::GetDocument() const
   { return reinterpret_cast<CMy3DViewerDoc*>(m_pDocument); }
#endif

