#include "pch.h"
#include "StateManager.h"
#include "ChildView.h"


State::State()
	: statetype(eState_Cnt)
	, SDelta(0)
{

}

State::State(EState InState)
	: statetype(InState)
	, SDelta(0)
{

}


State_Idle::State_Idle()
	: frame(0)
{
	load = new Gdiplus::Image(TEXT("Asset\\pidle.png"));

	for (int i = 0; i < 2; ++i)
	{
		int x = i * 128;
		rects.emplace_back(Gdiplus::Rect(x, 0, 128, 128));
	}
}

void State_Idle::Begin()
{

};

void State_Idle::Update(float Delta)
{
	SDelta += Delta;

	if (SDelta > 0.3f)
	{
		SDelta = 0;
		++frame;
		if (frame > rects.size() - 1)
			frame = 0;
	}

	Gdiplus::Rect Dst(0, 0, 128, 128);
	//불러올 이미지의 크기를 결정.
	Gdiplus::Bitmap bm(128, 128, PixelFormat32bppARGB);
	Gdiplus::Graphics test(&bm);
	test.DrawImage(load, Dst, rects[frame].X, rects[frame].Y, rects[frame].Width,
		rects[frame].Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	if (bleft)
		bm.RotateFlip(Gdiplus::Rotate180FlipY);

	//그려줄 이미지의 크기를 결정
	Gdiplus::Rect Dst2(x, 0, 90, 90);
	if(StateManager::GetInstance()->MemG != nullptr)
		StateManager::GetInstance()->MemG->DrawImage(&bm, Dst2);
}

/*

void State_Idle::Update(float Delta, Gdiplus::Graphics* MemG)
{
	SDelta += Delta;

	if (SDelta > 0.01f)
	{
		SDelta = 0;
		++frame;
		if (frame > rects.size() - 1)
			frame = 0;
	}

	Gdiplus::Rect Dst(0, 0, 108, 149);
	//불러올 이미지의 크기를 결정.
	Gdiplus::Bitmap bm(108, 149, PixelFormat32bppARGB);
	Gdiplus::Graphics test(&bm);
	test.DrawImage(load, Dst, rects[frame].X, rects[frame].Y, rects[frame].Width,
		rects[frame].Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	if (bleft)
		bm.RotateFlip(Gdiplus::Rotate180FlipY);

	//그려줄 이미지의 크기를 결정
	Gdiplus::Rect Dst2(x, 0, 90, 90);

	MemG->DrawImage(&bm, Dst2);
}

*/
void State_Idle::End()
{

};


bool State_Idle::ChangeState(EState InState)
{
	switch (InState)
	{
	case eState_Move:
		return true;
	}
	return	false;
};

State_Move::State_Move()
	: frame(0)
{
	load = new Gdiplus::Image(TEXT("Asset\\pmove.png"));

	for (int i = 0; i < 4; ++i)
	{
		int x = i * 128;
		rects.emplace_back(Gdiplus::Rect(x, 0, 128, 128));
	}
}

void State_Move::Begin()
{

}

void State_Move::Update(float Delta)
{
	SDelta += Delta;

	if (SDelta > 0.1f)
	{
		SDelta = 0;
		++frame;
		if (frame > rects.size() - 1)
			frame = 0;
	}

	Gdiplus::Rect Dst(0, 0, 128, 128);
	Gdiplus::Bitmap bm(128, 128, PixelFormat32bppARGB);
	Gdiplus::Graphics test(&bm);
	test.DrawImage(load, Dst, rects[frame].X, rects[frame].Y,
		rects[frame].Width, rects[frame].Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);


	if (bleft)
	{
		x -= 10;
		bm.RotateFlip(Gdiplus::Rotate180FlipY);
	}
	else
		x += 10;

	if (bup)
	{
		//y -= 10;
	}
	else
		//y += 10;
		;

	Gdiplus::Rect Dst2(x, y, 90, 90);


	//StateManager::GetInstance()->MemG->DrawImage(&bm, Dst2);
	//MemG->DrawImage(&bm, Dst2);
}

void StateManager::Render(Gdiplus::Graphics* DC)
{

}

void State_Move::End()
{

}
bool State_Move::ChangeState(EState InState)
{
	switch (InState)
	{
	case eState_Idle:
		return true;
	}
	return false;
};

StateManager::StateManager()
	: CurState(eState_Idle)
{

}

void StateManager::Add(State* pState)
{
	statelist.emplace_back(pState);
}

bool StateManager::ChangeState(EState InState)
{
	if (statelist[CurState]->ChangeState(InState))
	{
		statelist[CurState]->End();
		CurState = InState;
		statelist[CurState]->Begin();
		return true;
	}

	return false;
}

void StateManager::Update(float Delta)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		bleft = true;
		ChangeState(eState_Move);
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		bleft = false;
		ChangeState(eState_Move);
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		bup = true;
		ChangeState(eState_Move);
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		bup = false;
		ChangeState(eState_Move);
	}
	else
	{
		ChangeState(eState_Idle);
	}

	statelist[CurState]->Update(Delta);
	//statelist[CurState]->Update(Delta, MemG);
}




/*

void StateManager::Update(float Delta, Gdiplus::Graphics* MemG)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		bleft = true;
		ChangeState(eState_Move);
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		bleft = false;
		ChangeState(eState_Move);
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		bup = true;
		ChangeState(eState_Move);
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		bup = false;
		ChangeState(eState_Move);
	}
	else
	{
		ChangeState(eState_Idle);
	}

	statelist[CurState]->Update(Delta, MemG);
}

*/