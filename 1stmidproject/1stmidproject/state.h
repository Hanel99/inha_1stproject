#pragma once

#include <vector>
class State;
static bool bleft = false;
static int x;


class State
{
public:
	State();
	State(EState InState);

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
	State_Idle();
	void Begin() override;
	void Update(float Delta, Gdiplus::Graphics* MemG) override;
	void End() override;
	bool ChangeState(EState InState) override;

private:
	std::vector<Gdiplus::Rect> rects;
	int frame;
	Gdiplus::Image* load;
};

class State_Move : public State
{
public:
	State_Move();
	void Begin() override;
	void Update(float Delta, Gdiplus::Graphics* MemG)override;
	void End() override;
	bool ChangeState(EState InState) override;

private:
	int frame;
	Gdiplus::Image* load;
	std::vector<Gdiplus::Rect> rects;
};


class StateManager
{
public:
	StateManager();
	void Add(State* pState);
	bool ChangeState(EState InState);
	void Update(float Delta, Gdiplus::Graphics* MemG);

private:
	EState CurState;
	std::vector<State*> statelist;
};
