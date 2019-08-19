#pragma once
#include "Scene.h"

// 스탯
#define STATX_WIDTH 560 // 위치값
#define STATY_HEIGHT 155 // 위치값
#define STAT_WIDTH 100 // 길이값
#define STAT_HEIGHT 53 // 높이값

// 퍼센트 스탯
#define STATPX_WIDTH 680 // 위치값
#define STATPY_HEIGHT 160 // 위치값
#define STATP_WIDTH 113 // 길이값
#define STATP_HEIGHT 42 // 길이값

// 사이 간격
#define STAT_HITV 39 // 스탯 위아래 사이 간격
#define STATP_HITV 50 // 스탯 퍼센트 위아래 사이 간격
#define MINISTAT_HITV 65 // 왼쪽 작은 스탯 버튼 위아래 사이 간격

// 스탯 업그레이드
#define STATUX_WIDTH 1002 // 위치값
#define STATUY_HEIGHT 160 // 위치값

// 스탯 업그레이드 퍼센트
#define STATUPX_WIDTH 1131 // 위치값

// 왼쪽 작은 스탯 버튼
#define LMINISTATX_WIDTH 1058 // 위치값
#define LMINISTATY_HEIGHT 192 // 위치값
#define LMINISTAT_WIDTH 66 // 길이값
#define LMINISTAT_HEIGHT 28 // 길이값

// 오른쪽 작은 스탯 버튼
#define RMINISTATX_WIDTH 1187 // 위치값


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

public:
	std::weak_ptr<Gdiplus::Image> statImg;
	std::weak_ptr<Gdiplus::Image> bgImg;

};
