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
	, addDelta2(0)
	, isSafe(false)
	, isDamaged(false)
{
	Init();
}

Player::~Player()
{
	Release();
}

void Player::Init()
{
	width = 35;
	height = 42;
	r = width / 2;
	center.x = GetX() + width / 2;
	center.y = GetY() + height / 2;
	P_Shild = new Gdiplus::SolidBrush(Gdiplus::Color(100, 61, 200, 185));
}

void Player::Release()
{
	delete P_Shild;
}

void Player::Update(float Delta)
{	
	if (isDamaged)
	{
		addDelta += Delta;
		if (addDelta > 1.5f)
		{
			isDamaged = false;
		}
	}
	else
	{
		addDelta = 0;
	}

	if (isSafe)
	{
		addDelta2 += Delta;
		if (addDelta2 > 1.5f)
		{
			isSafe = false;
		}
	}
	else
	{
		addDelta2 = 0;
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

	if (EXP >= 1000)
	{
		EXP -= 1000;
		skillPoint += 10;
		LV += 10;
	}
	else if (EXP >= 100)
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
	

	if (isDamaged) //피격 & 무적상태라면
	{
		float R = 255.0f;
		float alpha = 0.5f;
		//피격상태임을 표시할 반투명 빨간 플레이어 이미지 처리
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

	if (isSafe) //실드를 쓴 상태라면
	{
		MemG->FillEllipse(P_Shild, center.x - (8 * r), center.y - (8 * r), 16 * r, 16 * r);
	}
}
