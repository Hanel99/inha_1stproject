#pragma once
#include "Scene.h"

// 숫자 출력 스테이터스 L
#define LSTATNUM_WIDTH 575
#define LSTATNUM_HEIGHT 168

// 위아래 간격
#define STATITV 92

// 숫자 출력 스테이터스 R
#define RSTATNUM_WIDTH 694


// 숫자 출력 스테이터스 강화 L
#define LSTATUPNUM_WIDTH 1016
#define LSTATUPNUM_HEIGHT 168

// 숫자 출력 스테이터스 강화 R
#define RSTATUPNUM_WIDTH 1145

// 작은 버튼 L
#define LMSTATNUM_WIDTH 1067
#define LMSTATNUM_HEIGHT 197

// 작은 버튼 R
#define RMSTATUM_WIDTH 1196

// 간격
#define MSTATITV 93


// 스탯 업그레이드
#define STATUX_WIDTH 1002 // 위치값
#define STATUY_HEIGHT 160 // 위치값
#define STATUB_WIDTH 113 // 버튼길이
#define STATUB_HEIGHT 42 // 버튼길이
// 스탯 업그레이드 퍼센트
#define STATUPX_WIDTH 1131 // 위치값
#define STATP_HITV 50 // 스탯 퍼센트 위아래 사이 간격




class StatusScene : public Scene
{
public:
	StatusScene();

	void Init();
	void Update(float Delta);
	void Render(Gdiplus::Graphics* MemG);
	void SendLButtonDown(UINT nFlags, CPoint point);
	void SendRButtonDown(UINT nFlags, CPoint point);
	
	Gdiplus::PointF P;
	std::wstring tempStr;

	Player* player;

public:
	std::weak_ptr<Gdiplus::Image> statImg;
	std::weak_ptr<Gdiplus::Image> bgImg;
};
