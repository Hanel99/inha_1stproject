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
	Gdiplus::Rect screenPosRect(GetX(), GetY(), 100, 100);

	MemG->DrawImage(&bm, screenPosRect);

}
