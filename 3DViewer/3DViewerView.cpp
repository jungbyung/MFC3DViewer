
// 3DViewerView.cpp : CMy3DViewerView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "3DViewer.h"
#endif

#include "3DViewerDoc.h"
#include "3DViewerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy3DViewerView

IMPLEMENT_DYNCREATE(CMy3DViewerView, CView)

BEGIN_MESSAGE_MAP(CMy3DViewerView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_32771, &CMy3DViewerView::On32771)
	ON_COMMAND(ID_32772, &CMy3DViewerView::On32772)
	ON_COMMAND(ID_32773, &CMy3DViewerView::On32773)
	ON_COMMAND(ID_32774, &CMy3DViewerView::On32774)
	ON_COMMAND(ID_32775, &CMy3DViewerView::On32775)
	ON_COMMAND(ID_32776, &CMy3DViewerView::On32776)
	ON_COMMAND(ID_32777, &CMy3DViewerView::On32777)
	ON_COMMAND(test, &CMy3DViewerView::Ontest)
	ON_COMMAND(ID_32778, &CMy3DViewerView::Onloadobj)
	ON_COMMAND(ID_32780, &CMy3DViewerView::On32780)
	ON_COMMAND(ID_32781, &CMy3DViewerView::On32781)
	ON_COMMAND(ID_32782, &CMy3DViewerView::On32782)
END_MESSAGE_MAP()

// CMy3DViewerView ����/�Ҹ�

CMy3DViewerView::CMy3DViewerView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_pMain = nullptr;

}

CMy3DViewerView::~CMy3DViewerView()
{
}

BOOL CMy3DViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CMy3DViewerView �׸���

void CMy3DViewerView::OnDraw(CDC* pDC)
{
	CMy3DViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.

	CRect rc;
	GetClientRect(rc);

	m_memDC.PatBlt(0, 0, rc.Width(), rc.Height(), WHITENESS);

	m_pMain->Draw(&m_memDC);

	pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &m_memDC, 0, 0, SRCCOPY);
	

}


// CMy3DViewerView �μ�

BOOL CMy3DViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMy3DViewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMy3DViewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CMy3DViewerView ����

#ifdef _DEBUG
void CMy3DViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DViewerDoc* CMy3DViewerView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DViewerDoc)));
	return (CMy3DViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3DViewerView �޽��� ó����
LRESULT CMy3DViewerView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pMain)
		m_pMain->WndProc(g_hWnd, message, wParam, lParam);
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:

		CDC* m_pDC = GetDC();
		m_pMain->Update();
		OnDraw(m_pDC);
		ReleaseDC(m_pDC);
		break;
	}
	return CView::WindowProc(message, wParam, lParam);
}


BOOL CMy3DViewerView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CView::PreTranslateMessage(pMsg);
}


void CMy3DViewerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	m_pMain = new cMain();
	m_pMain->Init();

	SetTimer(0, 10, nullptr);
	CRect rc;
	GetClientRect(rc);

	CDC* pDC = GetDC();
	m_memDC.CreateCompatibleDC(pDC);
	m_bmp.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	m_pOldBitmap = (CBitmap*)m_memDC.SelectObject(&m_bmp);
}


BOOL CMy3DViewerView::DestroyWindow()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	KillTimer(0);

	m_memDC.SelectObject(m_pOldBitmap);
	m_memDC.DeleteDC();

	return CView::DestroyWindow();
}

//����
void CMy3DViewerView::On32771()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_pMain->SetParallel();
}

//����
void CMy3DViewerView::On32772()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_pMain->SetPerspective();
}

//����
void CMy3DViewerView::On32773()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_pMain->AddFigure(0);
}

//��
void CMy3DViewerView::On32774()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_pMain->AddFigure(1);
}

//����
void CMy3DViewerView::On32775()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_pMain->AddFigure(2);
}


void CMy3DViewerView::On32776()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_pMain->SetWire();
}


void CMy3DViewerView::On32777()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_pMain->SetSolid();
}


void CMy3DViewerView::Ontest()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
}


void CMy3DViewerView::Onloadobj()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_pMain->AddFigure(3);
	char szFilter[] = "obj (*.obj) |*.obj||";
	CFileDialog dlg(TRUE, nullptr, nullptr, OFN_HIDEREADONLY, szFilter);

	if (IDOK == dlg.DoModal())
	{
		m_pMain->str = dlg.GetPathName();
		
	}
}


void CMy3DViewerView::On32780()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_pMain->AddFigure(4);
}


void CMy3DViewerView::On32781()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		COLORREF ref = dlg.GetColor();
		int r = GetRValue(ref);
		int g = GetGValue(ref);
		int b = GetBValue(ref);
		m_pMain->SetColor(jbMath::Vector3(r,g,b));
	}
}


void CMy3DViewerView::On32782()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		COLORREF ref = dlg.GetColor();
		int r = GetRValue(ref);
		int g = GetGValue(ref);
		int b = GetBValue(ref);
		m_pMain->SetWireColor(jbMath::Vector3(r, g, b));
	}
}
