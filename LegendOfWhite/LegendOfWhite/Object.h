#pragma once
#include "pch.h"

class Object
{
public:
	Object()
		: Objtype(eObjectType_None)
	{

	}

	Object(EObjectType InType)
		: Objtype(InType)
	{

	}

	virtual void Begin() {}
	virtual void Update(float Delta) {}
	virtual void End() {}

	void SetXY(int getx, int gety)
	{
		x = getx;
		y = gety;
	}
	int GetX()
	{
		return x;
	}
	int GetY()
	{
		return y;
	}

public:
	//Gdiplus::Image* ParentImg;
	//Gdiplus::Bitmap Img;

	//CRect rc;
	EObjectType Objtype;
	int x;
	int y;
};