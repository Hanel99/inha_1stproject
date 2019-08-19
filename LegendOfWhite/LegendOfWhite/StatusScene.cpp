#include "pch.h"
#include "StatusScene.h"

#define _CRT_SECURE_NO_WARNINGS

StatusScene::StatusScene()
{
	player = GameData::GetInstance()->player;
}

void StatusScene::Init()
{
}

void StatusScene::Update(float Delta)
{
	//게임씬으로
	if (GetAsyncKeyState(VK_TAB) & 0x1001)
	{
		SceneManager::GetInstance()->SwapStatusScene();
	}

	player->ATK = (player->LV + GameData::GetInstance()->ATKP) * (1 + GameData::GetInstance()->ATKM);
	player->SPD = 300 + (GameData::GetInstance()->SPDP * (1 + GameData::GetInstance()->SPDM)) * 0.5f;
	player->SSPD = GameData::GetInstance()->SSPDP * (1 + GameData::GetInstance()->SSPDM);
	player->HP = GameData::GetInstance()->HP;
	player->CRI = GameData::GetInstance()->CRI;
}

void StatusScene::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	statImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\statImg.png"));

	temp.DrawImage(statImg.lock().get(),
		rect, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);


	//그려줄 screen좌표의 rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Font F(L"맑은고딕", 20, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush B(Gdiplus::Color(255, 255, 255));

	// 스테이터스 L
	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT;
	tempStr = std::to_wstring(player->ATK);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV;
	tempStr = std::to_wstring(player->SSPD);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
	tempStr = std::to_wstring(player->SPD);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 3;
	tempStr = std::to_wstring(player->HP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 4;
	tempStr = std::to_wstring((int)(player->CRI * 100)) + L"%";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	// 스테이터스 R
	P.X = RSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT;
	tempStr = std::to_wstring(player->LV) + L"+";
	tempStr.append(std::to_wstring(GameData::GetInstance()->ATKP) + L" * ");
	tempStr.append(std::to_wstring((int)(GameData::GetInstance()->ATKM * 100)));
	tempStr.append(L"%");
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV;
	tempStr = std::to_wstring(GameData::GetInstance()->SSPDP) + L" * ";
	tempStr.append(std::to_wstring((int)(GameData::GetInstance()->SSPDM * 100)));
	tempStr.append(L"%");
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
	tempStr = std::to_wstring(GameData::GetInstance()->SPDP) + L" * ";
	tempStr.append(std::to_wstring((int)(GameData::GetInstance()->SPDM * 100)));
	tempStr.append(L"%");
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	// 스테이터스 강화 L
	P.X = LSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV;
	tempStr = std::to_wstring(GameData::GetInstance()->SSPDP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
	tempStr = std::to_wstring(GameData::GetInstance()->SPDP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 3;
	tempStr = std::to_wstring(GameData::GetInstance()->HP);
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	// 스테이터스 강화 R

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->ATKM * 100)) + L"%";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->SSPDM * 100)) + L"%";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->SPDM * 100)) + L"%";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 3;
	tempStr = L"+1";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 4;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->CRI * 100)) + L"%";
	temp.DrawString(tempStr.c_str(), -1, &F, P, &B);

	// 작은 버튼 L
	Gdiplus::Font F2(L"맑은고딕", 13, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush B2(Gdiplus::Color(255, 255, 255));

	P.X = LMSTATNUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT;
	tempStr = L"1pt";
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = LMSTATNUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV;
	tempStr = L"1pt";
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = LMSTATNUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 2;
	tempStr = L"1pt";
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = LMSTATNUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 3;
	tempStr = std::to_wstring((int)((GameData::GetInstance()->HP - 2) * 10)) + L"pt";
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	// 작은 버튼 R
	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->ATKM * 100 / 5 + 2)) + L"pt";
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->SSPDM * 100 / 5 + 2)) + L"pt";
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 2;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->SPDM * 100 / 5 + 2)) + L"pt";
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 3;
	tempStr = std::to_wstring(GameData::GetInstance()->healCount) + L"pt";
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 4;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->CRI * 100 / 5 + 2)) + L"pt";
	temp.DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	//레벨과 잔여포인트 표시
	Gdiplus::Font F3(L"맑은고딕", 30, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	P.X = 10;
	P.Y = 10;
	tempStr = L"LV : " + std::to_wstring(player->LV);
	temp.DrawString(tempStr.c_str(), -1, &F3, P, &B);

	P.X = 10;
	P.Y = 40;
	tempStr = L"Skillpoint : " + std::to_wstring(player->skillPoint);
	temp.DrawString(tempStr.c_str(), -1, &F3, P, &B);



	MemG->DrawImage(&bm, screenPosRect);
}

void StatusScene::SendLButtonDown(UINT nFlags, CPoint point)
{
	if (player->skillPoint > 0)
	{
		--player->skillPoint;
		GameData::GetInstance()->ATKP++;
	}
}

void StatusScene::SendRButtonDown(UINT nFlags, CPoint point)
{
}
