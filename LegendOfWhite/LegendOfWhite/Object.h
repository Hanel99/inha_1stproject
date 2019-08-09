#pragma once


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

public:
	//Gdiplus::Image* ParentImg;
	//Gdiplus::Bitmap Img;

	//CRect rc;
	EObjectType Objtype;
	int objx;
	int objy;
};