#pragma once
#include "pch.h"
#include "SingleTon.h"
//#include <afxwin2.inl>

class MouseManager : public Singleton<MouseManager>
{
public:
	MouseManager();
	~MouseManager();

	static inline POINT GetMousePos(void)
	{
		POINT   pt;
		GetCursorPos(&pt);
		::ScreenToClient(AfxGetMainWnd()->GetSafeHwnd(), &pt);

		return pt;
	}
};