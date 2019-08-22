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
	if (GetAsyncKeyState(VK_UP)  && GetAsyncKeyState(VK_DOWN))
	{
		GameData::GetInstance()->ATKP = 10000;
		GameData::GetInstance()->SPDM = 1000;
		GameData::GetInstance()->SSPDM = 1000;
		GameData::GetInstance()->MAXHP = 10000;
		GameData::GetInstance()->player->HP = 10000;
		GameData::GetInstance()->player->CRI = 0.8f;
	}

	player->ATK = (player->LV + GameData::GetInstance()->ATKP) * (1 + GameData::GetInstance()->ATKM);
	player->SPD = 500 + (GameData::GetInstance()->SPDP * (1 + GameData::GetInstance()->SPDM) * 1.5f);
	player->SSPD = 800 + (GameData::GetInstance()->SSPDP * (1 + GameData::GetInstance()->SSPDM) * 3.0f);
	player->CRI = GameData::GetInstance()->CRI;
}

void StatusScene::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Rect recttab(336, 180, 40, 330);
	tabImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\tab.png"));
	MemG->DrawImage(tabImg.lock().get(), recttab);

	statImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\statImg.png"));
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);
	MemG->DrawImage(statImg.lock().get(), screenPosRect);

	//그려줄 screen좌표의 rect
	

	Gdiplus::Font F(L"맑은고딕", 20, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush B(Gdiplus::Color(255, 255, 255));

	// 스테이터스 L
	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT;
	tempStr = std::to_wstring(player->ATK);
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV;
	//tempStr = std::to_wstring(player->SSPD);
	tempStr = std::to_wstring((int)(GameData::GetInstance()->SSPDP * (1 + GameData::GetInstance()->SSPDM)));
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
	//tempStr = std::to_wstring(player->SPD);
	tempStr = std::to_wstring((int)(GameData::GetInstance()->SPDP * (1 + GameData::GetInstance()->SPDM)));
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 3;
	tempStr = std::to_wstring(player->HP);
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 4;
	tempStr = std::to_wstring((int)(player->CRI * 100)) + L"%";
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	// 스테이터스 R
	P.X = RSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT;
	Gdiplus::Font F0(L"맑은고딕", 16, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	tempStr = std::to_wstring(player->LV) + L"+";
	tempStr.append(std::to_wstring(GameData::GetInstance()->ATKP) + L" * ");
	tempStr.append(std::to_wstring((int)(GameData::GetInstance()->ATKM * 100)));
	tempStr.append(L"%");
	MemG->DrawString(tempStr.c_str(), -1, &F0, P, &B);

	P.X = RSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV;
	tempStr = std::to_wstring(GameData::GetInstance()->SSPDP) + L" * ";
	tempStr.append(std::to_wstring((int)(GameData::GetInstance()->SSPDM * 100)));
	tempStr.append(L"%");
	MemG->DrawString(tempStr.c_str(), -1, &F0, P, &B);

	P.X = RSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
	tempStr = std::to_wstring(GameData::GetInstance()->SPDP) + L" * ";
	tempStr.append(std::to_wstring((int)(GameData::GetInstance()->SPDM * 100)));
	tempStr.append(L"%");
	MemG->DrawString(tempStr.c_str(), -1, &F0, P, &B);

	// 스테이터스 강화 L
	P.X = LSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT;
	tempStr = std::to_wstring(GameData::GetInstance()->ATKP);
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV;
	tempStr = std::to_wstring(GameData::GetInstance()->SSPDP);
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
	tempStr = std::to_wstring(GameData::GetInstance()->SPDP);
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 3;
	tempStr = std::to_wstring(GameData::GetInstance()->MAXHP);
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	// 스테이터스 강화 R

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->ATKM * 100)) + L"%";
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->SSPDM * 100)) + L"%";
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->SPDM * 100)) + L"%";
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 3;
	tempStr = L"+1";
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = RSTATUPNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 4;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->CRI * 100)) + L"%";
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	// 작은 버튼 L
	Gdiplus::Font F2(L"맑은고딕", 13, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush B2(Gdiplus::Color(255, 255, 255));

	P.X = LMSTATNUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT;
	tempStr = L"1pt";
	MemG->DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = LMSTATNUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV;
	tempStr = L"1pt";
	MemG->DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = LMSTATNUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 2;
	tempStr = L"1pt";
	MemG->DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = LMSTATNUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 3;
	tempStr = std::to_wstring((int)((GameData::GetInstance()->MAXHP - 2) * 10)) + L"pt";
	MemG->DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	// 작은 버튼 R
	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->ATKM * 100 / 5 + 2)) + L"pt";
	MemG->DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->SSPDM * 100 / 5 + 2)) + L"pt";
	MemG->DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 2;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->SPDM * 100 / 5 + 2)) + L"pt";
	MemG->DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 3;
	tempStr = std::to_wstring(GameData::GetInstance()->healCount) + L"pt";
	MemG->DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	P.X = RMSTATUM_WIDTH;
	P.Y = LMSTATNUM_HEIGHT + MSTATITV * 4;
	tempStr = std::to_wstring((int)(GameData::GetInstance()->CRI * 100 / 5 + 2)) + L"pt";
	MemG->DrawString(tempStr.c_str(), -1, &F2, P, &B2);

	//레벨과 잔여포인트 표시
	Gdiplus::Font F3(L"Berlin Sans FB", 28, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
	Gdiplus::SolidBrush B3(Gdiplus::Color(126, 109, 225)); // SP 색
	Gdiplus::SolidBrush B7(Gdiplus::Color(228, 39, 39)); // HP 색

	// Lv
	P.X = 12;
	P.Y = 8;
	tempStr = L"Lv. " + std::to_wstring(player->LV);
	MemG->DrawString(tempStr.c_str(), -1, &F3, P, &B);

	//HP
	P.X = 150;
	P.Y = 8;
	tempStr = L"HP : " + std::to_wstring(player->HP);
	MemG->DrawString(tempStr.c_str(), -1, &F3, P, &B7);

	// SP
	P.X = 204;
	P.Y = 42;
	tempStr = L"SP " + std::to_wstring(player->skillPoint);
	MemG->DrawString(tempStr.c_str(), -1, &F3, P, &B3);
}

void StatusScene::SendLButtonDown(UINT nFlags, CPoint point)
{	
	// 탭 닫기
	if (MouseManager::GetInstance()->GetMousePos().x >= 336 && MouseManager::GetInstance()->GetMousePos().x <= 376
		&& MouseManager::GetInstance()->GetMousePos().y >= 180 && MouseManager::GetInstance()->GetMousePos().y <= 510)
	{
		SceneManager::GetInstance()->SwapStatusScene();
	}


	// 공격력 합
	if (MouseManager::GetInstance()->GetMousePos().x >= STATUX_WIDTH && MouseManager::GetInstance()->GetMousePos().x <= STATUX_WIDTH + STATUB_WIDTH
		&& MouseManager::GetInstance()->GetMousePos().y >= STATUY_HEIGHT && MouseManager::GetInstance()->GetMousePos().y <= STATUY_HEIGHT + STATUB_HEIGHT)
	{

		if (player->skillPoint > 0)
		{
			--player->skillPoint;
			GameData::GetInstance()->ATKP++;
		}
	}
	
	// 공격력 곱
	if (MouseManager::GetInstance()->GetMousePos().x >= STATUPX_WIDTH && MouseManager::GetInstance()->GetMousePos().x <= STATUPX_WIDTH + STATUB_WIDTH
		&& MouseManager::GetInstance()->GetMousePos().y >= STATUY_HEIGHT && MouseManager::GetInstance()->GetMousePos().y <= STATUY_HEIGHT + STATUB_HEIGHT)
	{
		if (player->skillPoint >= GameData::GetInstance()->ATKM * 100 / 5 + 2)
		{
			player->skillPoint -= GameData::GetInstance()->ATKM * 100 / 5 + 2;
			GameData::GetInstance()->ATKM += 0.1f;
		}
	}

	// 공격속도 합
	if (MouseManager::GetInstance()->GetMousePos().x >= STATUX_WIDTH && MouseManager::GetInstance()->GetMousePos().x <= STATUX_WIDTH + STATUB_WIDTH
		&& MouseManager::GetInstance()->GetMousePos().y >= STATUY_HEIGHT + STATUB_HEIGHT + STATP_HITV 
		&& MouseManager::GetInstance()->GetMousePos().y <= STATUY_HEIGHT + STATUB_HEIGHT * 2 + STATP_HITV)
	{

		if (player->skillPoint > 0)
		{
			--player->skillPoint;
			GameData::GetInstance()->SSPDP++;
		}
	}

	// 공격속도 곱
	if (MouseManager::GetInstance()->GetMousePos().x >= STATUPX_WIDTH && MouseManager::GetInstance()->GetMousePos().x <= STATUPX_WIDTH + STATUB_WIDTH
		&& MouseManager::GetInstance()->GetMousePos().y >= STATUY_HEIGHT + STATUB_HEIGHT + STATP_HITV 
		&& MouseManager::GetInstance()->GetMousePos().y <= STATUY_HEIGHT + STATUB_HEIGHT * 2 + STATP_HITV)
	{

		if (player->skillPoint >= GameData::GetInstance()->SSPDM * 100 / 5 + 2)
		{
			player->skillPoint -= GameData::GetInstance()->SSPDM * 100 / 5 + 2;
			GameData::GetInstance()->SSPDM += 0.1f;
		}
	}

	// 이동속도 합
	if (MouseManager::GetInstance()->GetMousePos().x >= STATUX_WIDTH && MouseManager::GetInstance()->GetMousePos().x <= STATUX_WIDTH + STATUB_WIDTH
		&& MouseManager::GetInstance()->GetMousePos().y >= STATUY_HEIGHT + STATUB_HEIGHT *2 + STATP_HITV * 2
		&& MouseManager::GetInstance()->GetMousePos().y <= STATUY_HEIGHT + STATUB_HEIGHT * 3 + STATP_HITV * 2)
	{

		if (player->skillPoint > 0)
		{
			--player->skillPoint;
			GameData::GetInstance()->SPDP++;
		}
	}

	// 이동속도 곱
	if (MouseManager::GetInstance()->GetMousePos().x >= STATUPX_WIDTH && MouseManager::GetInstance()->GetMousePos().x <= STATUPX_WIDTH + STATUB_WIDTH
		&& MouseManager::GetInstance()->GetMousePos().y >= STATUY_HEIGHT + STATUB_HEIGHT * 2 + STATP_HITV * 2
		&& MouseManager::GetInstance()->GetMousePos().y <= STATUY_HEIGHT + STATUB_HEIGHT * 3 + STATP_HITV * 2)
	{

		if (player->skillPoint >= GameData::GetInstance()->SPDM * 100 / 5 + 2)
		{
			player->skillPoint -= GameData::GetInstance()->SPDM * 100 / 5 + 2;
			GameData::GetInstance()->SPDM += 0.1f;
		}
	}

	// 최대 체력
	if (MouseManager::GetInstance()->GetMousePos().x >= STATUX_WIDTH && MouseManager::GetInstance()->GetMousePos().x <= STATUX_WIDTH + STATUB_WIDTH
		&& MouseManager::GetInstance()->GetMousePos().y >= STATUY_HEIGHT + STATUB_HEIGHT * 3 + STATP_HITV * 3
		&& MouseManager::GetInstance()->GetMousePos().y <= STATUY_HEIGHT + STATUB_HEIGHT * 4 + STATP_HITV * 3)
	{

		if (player->skillPoint >= (GameData::GetInstance()->MAXHP - 2) * 10)
		{
			player->skillPoint -= (GameData::GetInstance()->MAXHP - 2) * 10;
			GameData::GetInstance()->MAXHP++;
		}
	}

	// 회복한 횟수
	if (MouseManager::GetInstance()->GetMousePos().x >= STATUPX_WIDTH && MouseManager::GetInstance()->GetMousePos().x <= STATUPX_WIDTH + STATUB_WIDTH
		&& MouseManager::GetInstance()->GetMousePos().y >= STATUY_HEIGHT + STATUB_HEIGHT * 3 + STATP_HITV * 3
		&& MouseManager::GetInstance()->GetMousePos().y <= STATUY_HEIGHT + STATUB_HEIGHT * 4 + STATP_HITV * 3)
	{

		if (player->skillPoint >= GameData::GetInstance()->healCount)
		{			
			if (GameData::GetInstance()->MAXHP > GameData::GetInstance()->player->HP)
			{
				player->skillPoint -= GameData::GetInstance()->healCount;
				GameData::GetInstance()->healCount++;
				GameData::GetInstance()->player->HP++;
			}
		}
	}

	// 크리티컬 확률
	if (MouseManager::GetInstance()->GetMousePos().x >= STATUPX_WIDTH && MouseManager::GetInstance()->GetMousePos().x <= STATUPX_WIDTH + STATUB_WIDTH
		&& MouseManager::GetInstance()->GetMousePos().y >= STATUY_HEIGHT + STATUB_HEIGHT * 4 + STATP_HITV * 4
		&& MouseManager::GetInstance()->GetMousePos().y <= STATUY_HEIGHT + STATUB_HEIGHT * 5 + STATP_HITV * 4)
	{

		if (player->skillPoint >= GameData::GetInstance()->CRI * 100 / 5 + 2)
		{
			player->skillPoint -= GameData::GetInstance()->CRI * 100 / 5 + 2;
			GameData::GetInstance()->CRI += 0.1f;
		}
	}
}

void StatusScene::SendRButtonDown(UINT nFlags, CPoint point)
{
	//좌클릭 10번
	for (int i = 0; i < 10; i++)
	{
		SendLButtonDown(nFlags, point);
	}
}
