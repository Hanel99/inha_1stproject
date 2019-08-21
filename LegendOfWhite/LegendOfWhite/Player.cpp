#include "pch.h"
#include "Player.h"


void Player::Update(float Delta)
{
	addDelta += Delta;
	//state머신을 바꿀것
	if ((GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('a') || GetAsyncKeyState('A')) & 0x8001)
	{
		eplayerlook = ePlayerLook_Left;
		SetX(GetX() - (Delta * SPD));
	}
	else if ((GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('d') || GetAsyncKeyState('D')) & 0x8001)
	{
		eplayerlook = ePlayerLook_Right;
		SetX(GetX() + (Delta * SPD));
	}
	else if ((GetAsyncKeyState(VK_UP) || GetAsyncKeyState('w') || GetAsyncKeyState('W')) & 0x8001)
	{
		eplayerlook = ePlayerLook_Up;
		SetY(GetY() - (Delta * SPD));
	}
	else if ((GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('s') || GetAsyncKeyState('S')) & 0x8001)
	{
		eplayerlook = ePlayerLook_Down;
		SetY(GetY() + (Delta * SPD));
	}

	center.x = GetX() + width / 2;
	center.y = GetY() + height / 2;

	if (EXP >= 100)
	{
		EXP -= 100;
		++skillPoint;
		++LV;
	}
}

void Player::Render(Gdiplus::Graphics* MemG)
{	
	playerimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\obj_spritesheet.png"));	
	switch (eplayerlook)
	{
	case ePlayerLook_Left:
		rec = AssetManager::GetInstance()->GetRect(eXMLType_Obj, eXMLObjnum_Pl1);
		break;
	case ePlayerLook_Right:
		rec = AssetManager::GetInstance()->GetRect(eXMLType_Obj, eXMLObjnum_Pr1);
		break;
	case ePlayerLook_Up:
		rec = AssetManager::GetInstance()->GetRect(eXMLType_Obj, eXMLObjnum_Pu1);
		break;
	case ePlayerLook_Down:
		rec = AssetManager::GetInstance()->GetRect(eXMLType_Obj, eXMLObjnum_Pd1);
		break;
	}
	//Player의 크기
	Gdiplus::Rect rect(0, 0, 35, 42);

	//Gdiplus::Bitmap bm(rec->Width, rec->Height, PixelFormat32bppARGB);
	//Gdiplus::Graphics temp(&bm);

	//temp.DrawImage(playerimg.lock().get(), rect, rec->X, rec->Y, rec->Width, rec->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), rec->Width, rec->Height);
	
	MemG->DrawImage(playerimg.lock().get(), screenPosRect, rec->X, rec->Y, rec->Width, rec->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//Gdiplus::Pen P(Gdiplus::Color(255, 0, 0), 5);
	//MemG->DrawEllipse(&P, (int)(center.x - r), (int)(center.y - r), r * 2, r * 2);
}
