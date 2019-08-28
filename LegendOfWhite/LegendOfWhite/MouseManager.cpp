#include "pch.h"
#include "MouseManager.h"

MouseManager::MouseManager()
{
}

MouseManager::~MouseManager()
{
}

POINT MouseManager::GetMousePos()
{
	POINT pt;
	GetCursorPos(&pt);
	if (AfxGetMainWnd() != nullptr)
	{
		::ScreenToClient(AfxGetMainWnd()->GetSafeHwnd(), &pt);
	}
	return pt;
}