#pragma once
#include "pch.h"

class Object
{
public:
	Object()
		: Objtype(eObjectType_None)
		, xy(0,0)
	{

	}

	Object(EObjectType InType)
		: Objtype(InType)
		, xy(0, 0)
	{

	}

	virtual void ProcessInput() = 0;
	virtual void Update(float Delta) = 0;
	virtual void Render(Gdiplus::Graphics* G) = 0;

	void SetXY(int getx, int gety)
	{
		xy.x = getx;
		xy.y = gety;
	}
	CPoint GetXY()
	{
		return xy;
	}
	int GetX()
	{
		return xy.x;
	}
	int GetY()
	{
		return xy.y;
	}

private:	
	CPoint xy;
	EObjectType Objtype;
};