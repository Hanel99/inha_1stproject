﻿
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "1stmidproject.h"
#include "ChildView.h"

#include "SceneManager.h"
#include "StateManager.h"
#include <vector>


//#ifdef _DEBUG
//#define new DEBUG_NEW
//#endif


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

	SceneManager::GetInstance()->LoadScene(CString("Scene_Start"));

	StateManager::GetInstance()->Add(new State_Idle());
	StateManager::GetInstance()->Add(new State_Move());

	//Statemanager.Add(new State_Idle());
	//Statemanager.Add(new State_Move());


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

	Gdiplus::SolidBrush WhiteBrush(Gdiplus::Color(255, 180, 180, 180));
	MemG.FillRectangle(&WhiteBrush, rc2);
	
	/////////////////////////////////////////

	//Gdiplus::Image img(TEXT("bgaimage.png"));
	//MemG.DrawImage(&img, 0, 0, rc.Width(), rc.Height());
	
	//Gdiplus::Rect rr(0, 0, rc.Width(), rc.Height());
	//Gdiplus::BitmapData pt;
	//BackBuffer.LockBits(&rr, Gdiplus::ImageLockModeWrite, PixelFormat32bppARGB, &pt);
	//grayscale(rr.Width / 2, rr.Height / 2, pt);
	//BackBuffer.UnlockBits(&pt);


	//////////////////////////////////////
	//이거 필요없다고 하셨던거같음 근데 없으면 안됨
	//static int PrevTick = GetTickCount();
	//static int Delta = 0;
	//Delta = GetTickCount() - PrevTick;

	//statemgr.Update(Delta * 0.001f, &MemG);
	
	
	//StateManager::GetInstance()->Update(Delta * 0.001f);
	

	//PrevTick = GetTickCount();
	//UpdateMove(Delta, &MemG);

	//
	// scene render

	MainG.DrawImage(&BackBuffer, 0, 0, rc.Width(), rc.Height());


	//싱글톤 적용한거 이렇게 쓰면 됨
	//Scene* s = SceneManager::GetInstance()->GetCurScene();





	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	

	//CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

	
	/*
	//프레임 표시하는건데 뭔가 이상행
	CMemDC memDC(dc, this);

	DWORD delta = GetTickCount() - theApp.PrevTick;
	DWORD value = delta == 0 ? 0 : 1000 / delta;
	CString temp;
	temp.Format(TEXT("%d"), value);
	memDC.GetDC().DrawText(temp, rc, DT_LEFT | DT_VCENTER);
	*/


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


/*

void grayscale(int width, int height, Gdiplus::BitmapData& pData)
{
	BYTE* pt = static_cast<BYTE*>(pData.Scan0);
	BYTE* pt2 = pt;
	for (int i = 0; i < height; ++i)
	{
		pt = pt2 + i * pData.Width * 4;
		for (int j = 0; j < width; ++j)
		{
			BYTE calc = *(pt) * 0.299 + *(pt + 1) * 0.587 + *(pt + 2) * 0.114;
			*(pt) = calc;
			*(pt+1) = calc;
			*(pt+2) = calc;
			pt += 4;
		}
	}
}


*/