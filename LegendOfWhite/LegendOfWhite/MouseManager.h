#pragma once
#include "pch.h"
#include "SingleTon.h"
//#include <afxwin2.inl>

class MouseManager : public Singleton<MouseManager>
{
public:
	MouseManager();
	~MouseManager();

	POINT GetMousePos();
};