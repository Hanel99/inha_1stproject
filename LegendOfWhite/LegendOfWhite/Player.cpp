#include "pch.h"
#include "Player.h"

void Player::ProcessInput()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		eplayerlook = ePlayerLook_Left;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		eplayerlook = ePlayerLook_Right;
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		eplayerlook = ePlayerLook_Up;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		eplayerlook = ePlayerLook_Down;
	}

}

void Player::Update(float Delta)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		SetX(GetX() - 1);
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		SetX(GetX() + 1);
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		SetY(GetY() - 1);
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		SetY(GetY() + 1);
	}
}

void Player::Render(Gdiplus::Graphics* MemG)
{
	//auto atlasImg = img.lock();
	//Player의 크기
	Gdiplus::Rect rect(0, 0, width, height);

	Gdiplus::Bitmap bm(width, height, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);
	//temp.DrawImage(playerAnimationList[state]->GetAtlasImg().lock().get(), rect, atlasRect.X, atlasRect.Y, atlasRect.Width, atlasRect.Height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);
	//Gdiplus::Image tempImg(TEXT("bgaimage.png"));
	
	switch (eplayerlook)
	{
	case ePlayerLook_Left:
		playerimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\pl.png"));
		break;
	case ePlayerLook_Right:
		playerimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\pr.png"));
		break;
	case ePlayerLook_Up:
		playerimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\pu.png"));
		break;
	case ePlayerLook_Down:
		playerimg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\pd.png"));
		break;
	}

	
	temp.DrawImage(playerimg.lock().get(),
		rect, 0, 0, width, height, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), 50, 50);

	MemG->DrawImage(&bm, screenPosRect);

}
