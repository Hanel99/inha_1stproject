#include "pch.h"
#include "StatusScene.h"

#define _CRT_SECURE_NO_WARNINGS

StatusScene::StatusScene()
{
	Init();
}

StatusScene::~StatusScene()
{
	Release();
}

void StatusScene::Init()
{
	player = GameData::GetInstance()->player;
}

void StatusScene::Release()
{

}

void StatusScene::Update(float Delta)
{
	//게임씬으로
	if (GetAsyncKeyState(VK_TAB) & 0x1001)
	{
		AssetManager::GetInstance()->PlaySound(eSound_BtnClick);
		SceneManager::GetInstance()->SwapStatusScene();
	}
	if (GetAsyncKeyState(VK_UP) && GetAsyncKeyState(VK_DOWN))
	{
		AssetManager::GetInstance()->PlaySound(eSound_GameClear);
		GameData::GetInstance()->ATKP = 1000;
		GameData::GetInstance()->SPDP = 300;
		GameData::GetInstance()->SSPDP = 300;
		GameData::GetInstance()->MAXHP = 1000;
		GameData::GetInstance()->player->HP = 1000;
		GameData::GetInstance()->CRI = 0.6f;
		player->skillPoint = 1000;
	}

	player->ATK = (player->LV + GameData::GetInstance()->ATKP) * (1 + GameData::GetInstance()->ATKM);
	player->SPD = 500 + (GameData::GetInstance()->SPDP * (1 + GameData::GetInstance()->SPDM) * 1.5f);
	player->SSPD = 800 + (GameData::GetInstance()->SSPDP * (1 + GameData::GetInstance()->SSPDM) * 3.0f);
	player->CRI = GameData::GetInstance()->CRI;
}

void StatusScene::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Rect rectTab(336, 180, 40, 330);
	tabImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\tab.png"));
	MemG->DrawImage(tabImg.lock().get(), rectTab);

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
	tempStr = std::to_wstring((int)(GameData::GetInstance()->SSPDP * (1 + GameData::GetInstance()->SSPDM)));
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);

	P.X = LSTATNUM_WIDTH;
	P.Y = LSTATNUM_HEIGHT + STATITV * 2;
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

	// SP
	P.X = 1158;
	P.Y = 88;
	tempStr = L"SP " + std::to_wstring(player->skillPoint);
	MemG->DrawString(tempStr.c_str(), -1, &F, P, &B);
}

void StatusScene::SendLButtonDown(UINT nFlags, CPoint point)
{
	AssetManager::GetInstance()->PlaySound(eSound_BtnClick);
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
		&& MouseManager::GetInstance()->GetMousePos().y >= STATUY_HEIGHT + STATUB_HEIGHT * 2 + STATP_HITV * 2
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
		if (player->skillPoint >= GameData::GetInstance()->CRI * 100 / 5 + 2 && player->CRI < 1.0f)
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