
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "1stmidproject.h"
#include "ChildView.h"

#include "SceneManager.h"
#include "state.h"
#include <vector>


//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif

Gdiplus::RectF ProgressRect(0, 0, 1000, 30);
Gdiplus::RectF ProgressRect2(0, 0, 1000, 30);
// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	SceneManager::GetInstance().LoadScene(CString("Scene_Start"));

	sm.Add(new State_Idle());
	sm.Add(new State_Move());


	return TRUE;
}



template<typename T>
float Lerp(T Start, T Dst, float dt)
{
	return (Dst - Start) * dt;
}


void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	

	Gdiplus::Graphics MainG(dc);

	CRect rc;
	GetClientRect(rc);
	Gdiplus::Rect rc2(rc.left, rc.top, rc.Width(), rc.Height());

	Gdiplus::Bitmap BackBuffer(rc.Width(), rc.Height(), PixelFormat32bppARGB);
	Gdiplus::Graphics MemG(&BackBuffer);

	Gdiplus::SolidBrush WhiteBrush(Gdiplus::Color(180, 180, 180, 180));
	MemG.FillRectangle(&WhiteBrush, rc2);

	//이거 필요없다고 하셨던거같음 근데 없으면 안됨
	static int PrevTick = GetTickCount();
	static int Delta = 0;
	Delta += GetTickCount() - PrevTick;
	sm.Update(Delta, &MemG);
	//UpdateMove(Delta, &MemG);

	//
	// scene render

	MainG.DrawImage(&BackBuffer, 0, 0, rc.Width(), rc.Height());


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CWnd::OnLButtonDown(nFlags, point);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return true;
	//return CWnd::OnEraseBkgnd(pDC);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CWinThread* pThread = AfxBeginThread(&CMy1stmidprojectApp::funcThread, NULL);
	return 0;
}
