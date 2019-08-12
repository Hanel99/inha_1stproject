#include "pch.h"
#include "Player.h"

void Player::ProcessInput()
{
}

void Player::Update(float Delta)
{
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
		playerimg = AssetManager::GetInstance()->GetImage(TEXT("pl.png"));
		break;
	case ePlayerLook_Right:
		playerimg = AssetManager::GetInstance()->GetImage(TEXT("pr.png"));
		break;
	case ePlayerLook_Up:
		playerimg = AssetManager::GetInstance()->GetImage(TEXT("pu.png"));
		break;
	case ePlayerLook_Down:
		playerimg = AssetManager::GetInstance()->GetImage(TEXT("pd.png"));
		break;
	}

	
	temp.DrawImage(playerimg.lock().get(),
		rect, 0, 0, 50, 50, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(GetX(), GetY(), width, height);

	MemG->DrawImage(&bm, screenPosRect);

}
