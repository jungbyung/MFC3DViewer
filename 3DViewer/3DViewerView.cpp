
// 3DViewerView.cpp : CMy3DViewerView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
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

// CMy3DViewerView 생성/소멸

CMy3DViewerView::CMy3DViewerView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_pMain = nullptr;

}

CMy3DViewerView::~CMy3DViewerView()
{
}

BOOL CMy3DViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy3DViewerView 그리기

void CMy3DViewerView::OnDraw(CDC* pDC)
{
	CMy3DViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.

	CRect rc;
	GetClientRect(rc);

	m_memDC.PatBlt(0, 0, rc.Width(), rc.Height(), WHITENESS);

	m_pMain->Draw(&m_memDC);

	pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &m_memDC, 0, 0, SRCCOPY);
	

}


// CMy3DViewerView 인쇄

BOOL CMy3DViewerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy3DViewerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy3DViewerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy3DViewerView 진단

#ifdef _DEBUG
void CMy3DViewerView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DViewerDoc* CMy3DViewerView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DViewerDoc)));
	return (CMy3DViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy3DViewerView 메시지 처리기
LRESULT CMy3DViewerView::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pMain)
		m_pMain->WndProc(g_hWnd, message, wParam, lParam);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CView::PreTranslateMessage(pMsg);
}


void CMy3DViewerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

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
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	KillTimer(0);

	m_memDC.SelectObject(m_pOldBitmap);
	m_memDC.DeleteDC();

	return CView::DestroyWindow();
}

//평행
void CMy3DViewerView::On32771()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_pMain->SetParallel();
}

//원근
void CMy3DViewerView::On32772()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_pMain->SetPerspective();
}

//상자
void CMy3DViewerView::On32773()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_pMain->AddFigure(0);
}

//구
void CMy3DViewerView::On32774()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_pMain->AddFigure(1);
}

//도넛
void CMy3DViewerView::On32775()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_pMain->AddFigure(2);
}


void CMy3DViewerView::On32776()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_pMain->SetWire();
}


void CMy3DViewerView::On32777()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_pMain->SetSolid();
}


void CMy3DViewerView::Ontest()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMy3DViewerView::Onloadobj()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_pMain->AddFigure(4);
}


void CMy3DViewerView::On32781()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
