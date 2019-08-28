#include "pch.h"
#include "Player.h"


Player::Player()
	: Object(EObjectType::eObjectType_Player)
	, HP(3)
	, ATK(1)
	, SPD(300)
	, SSPD(100)
	, CRI(0.0f)
	, LV(1)
	, EXP(0)
	, skillPoint(0)
	, eplayerlook(ePlayerLook_Down)
	, addDelta(0)
{
	width = 35;
	height = 42;
	r = width / 2;
	center.x = GetX() + width / 2;
	center.y = GetY() + height / 2;
}

Player::~Player()
{
}

void Player::Update(float Delta)
{	
	if (issafe)
	{
		addDelta += Delta;
		if (addDelta > 1.5f)
		{
			issafe = false;
		}
	}
	else
	{
		addDelta = 0;
	}

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

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), rec->Width, rec->Height);
	
	if (issafe)
	{
		float R = 255.0f;
		float alpha = 0.5f;
		//무적상태임을 표시할 반투명 빨간 플레이어 이미지 처리
		Gdiplus::ColorMatrix colorMatrix = { R, 0.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
									 0.0f, 0.0f, 0.0f, alpha, 0.0f,
									 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

		Gdiplus::ImageAttributes imageAtt;
		imageAtt.SetColorMatrix(&colorMatrix, Gdiplus::ColorMatrixFlagsDefault, Gdiplus::ColorAdjustTypeBitmap);

		MemG->DrawImage(playerimg.lock().get(), screenPosRect, rec->X, rec->Y, rec->Width, rec->Height, Gdiplus::Unit::UnitPixel, &imageAtt, 0, nullptr);
	}
	else
	{
		MemG->DrawImage(playerimg.lock().get(), screenPosRect, rec->X, rec->Y, rec->Width, rec->Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	}
}
