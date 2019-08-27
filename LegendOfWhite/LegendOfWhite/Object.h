#pragma once
#include "pch.h"

class Object
{
public:
	Object();
	Object(EObjectType inType);	

	virtual void Update(float Delta) = 0;
	virtual void Render(Gdiplus::Graphics* G) = 0;

	void SetX(float getx)
	{
		x = getx;
	}
	void SetY(float gety)
	{
		y = gety;
	}
	float GetX()
	{
		return x;
	}
	float GetY()
	{
		return y;
	}

public:
	int width;
	int height;
	int r;
	EObjectType Objtype;
private:
	float x;
	float y;
};