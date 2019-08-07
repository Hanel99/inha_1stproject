#pragma once

#include <vector>
class State;
static bool bleft = false;
static int x;


class State
{
public:
	State()
		: statetype(eState_Cnt)
	{

	}

	State(EState InState)
		: statetype(InState)
	{

	}

	virtual void Begin() = 0;
	virtual void Update(float Delta, Gdiplus::Graphics* MemG) = 0;
	virtual void End() = 0;
	virtual bool ChangeState(EState InState) = 0;


protected:
	EState statetype;
};

class State_Idle : public State
{
public:
	State_Idle()
		: frame(0)
	{
		load = new Gdiplus::Image(TEXT("Asset\\b.png"));
		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				int x = j * 108;
				int y = i * 149;

				rects.emplace_back(Gdiplus::Rect(x, y, 108, 149));
			}
		}
	}
	virtual void Begin() override
	{

	};

	virtual void Update(float Delta, Gdiplus::Graphics* MemG)override
	{
		if (Delta > 0.1f)
		{
			Delta = 0;
			++frame;
			if (frame > rects.size() - 1)
				frame = 0;
		}

		Gdiplus::Rect Dst(0, 0, 108, 149);
		Gdiplus::Bitmap bm(108, 149, PixelFormat32bppARGB);
		Gdiplus::Graphics test(&bm);
		test.DrawImage(load, Dst, rects[frame].X, rects[frame].Y, rects[frame].Width, rects[frame].Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);

		if (bleft)
			bm.RotateFlip(Gdiplus::Rotate180FlipY);

		Gdiplus::Rect Dst2(x, 0, 108, 149);

		MemG->DrawImage(&bm, Dst2);
	};
	virtual void End() override {};
	virtual bool ChangeState(EState InState) override
	{
		switch (InState)
		{
		case eState_Move:
			return true;
		}
		return	false;
	};

private:
	std::vector<Gdiplus::Rect> rects;
	int frame;
	Gdiplus::Image* load;
};

class State_Move : public State
{
public:
	State_Move()
		: frame(0)
	{
		load = new Gdiplus::Image(TEXT("Asset\\a.png"));
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				int x = j * 116;
				int y = i * 164;
				if (i == 3 && j == 5)
					break;
				rects.emplace_back(Gdiplus::Rect(x, y, 116, 164));
			}
		}
	}

	virtual void Begin() override
	{

	};

	virtual void Update(float Delta, Gdiplus::Graphics* MemG)override
	{
		if (Delta > 0.1f)
		{
			Delta = 0;
			++frame;
			if (frame > rects.size() - 1)
				frame = 0;
		}

		Gdiplus::Rect Dst(0, 0, 116, 164);
		Gdiplus::Bitmap bm(116, 164, PixelFormat32bppARGB);
		Gdiplus::Graphics test(&bm);
		test.DrawImage(load, Dst, rects[frame].X, rects[frame].Y, rects[frame].Width, rects[frame].Height, Gdiplus::Unit::UnitPixel,
			nullptr, 0, nullptr);

		if (bleft)
		{
			x -= 10;
			bm.RotateFlip(Gdiplus::Rotate180FlipY);
		}
		else
			x += 10;

		Gdiplus::Rect Dst2(x, 0, 108, 149);
		MemG->DrawImage(&bm, Dst2);
	};

	virtual void End() override {};
	virtual bool ChangeState(EState InState) override
	{
		switch (InState)
		{
		case eState_Idle:
			return true;
		}
		return false;
	};

private:
	int frame;
	Gdiplus::Image* load;
	std::vector<Gdiplus::Rect> rects;
};


class StateManager
{
public:
	StateManager()
		: CurState(eState_Idle)
	{

	}

	void Add(State* pState)
	{
		statelist.emplace_back(pState);
	}

	bool ChangeState(EState InState)
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

	void Update(float Delta, Gdiplus::Graphics* MemG)
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
		else
		{
			ChangeState(eState_Idle);
		}

		statelist[CurState]->Update(Delta, MemG);
	}

private:
	EState CurState;
	std::vector<State*> statelist;
};
