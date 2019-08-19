#include "pch.h"
#include "StatusScene.h"

#define _CRT_SECURE_NO_WARNINGS

StatusScene::StatusScene()
{
}

void StatusScene::Init()
{
}

void StatusScene::Update(float Delta)
{
	//���Ӿ�����
	if (GetAsyncKeyState(VK_TAB) & 0x1001)
	{
		SceneManager::GetInstance()->SwapStatusScene();
	}
}

void StatusScene::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	statImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\statImg.png"));

	temp.DrawImage(statImg.lock().get(),
		rect, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);


	//�׷��� screen��ǥ�� rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Font F(L"�������", 20, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush B(Gdiplus::Color(255, 255, 255));

	// �������ͽ� L
	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV;
	tempStr = L"1pt";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKM) + L"%";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 3;
	tempStr = std::to_wstring((GameData::GetInstance()->ATKM + 10) / 5) + L"pt";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 4;
	tempStr = std::to_wstring((GameData::GetInstance()->ATKM + 10) / 5) + L"pt";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	// �������ͽ� R
	P.X = RSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	// �������ͽ� ��ȭ L
	P.X = LSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 3;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	// �������ͽ� ��ȭ R

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 3;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 4;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	// ���� ��ư L
	Gdiplus::Font F2(L"�������", 13, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush B2(Gdiplus::Color(255, 255, 255));

	P.X = LMSTATNUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = LMSTATNUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = LMSTATNUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 2;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = LMSTATNUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 3;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	// ���� ��ư R
	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 2;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 3;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 4;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);


	



	//for (auto& it : objectVec)
	//{
		//it->Render(MemG);
	//}

	MemG->DrawImage(&bm, screenPosRect);
}

void StatusScene::SendLButtonDown(UINT nFlags, CPoint point)
{
}

void StatusScene::SendRButtonDown(UINT nFlags, CPoint point)
{
}
