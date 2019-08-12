#pragma once
#include "pch.h"

class State
{
public:
	State();
	~State();

	virtual void Begin() = 0;
	virtual void Update(float Delta, Gdiplus::Graphics* MemG) = 0;
	virtual void End() = 0;

protected:
	float SDelta;
};