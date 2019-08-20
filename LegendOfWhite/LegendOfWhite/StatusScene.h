#pragma once
#include "Scene.h"

// ���� ��� �������ͽ� L
#define LSTATNUM_WIDTH 575.0f
#define LSTATNUM_HEIGHT 168.0f

// ���Ʒ� ����
#define STATITV 92.0f

// ���� ��� �������ͽ� R
#define RSTATNUM_WIDTH 694.0f


// ���� ��� �������ͽ� ��ȭ L
#define LSTATUPNUM_WIDTH 1016.0f
#define LSTATUPNUM_HEIGHT 168.0f

// ���� ��� �������ͽ� ��ȭ R
#define RSTATUPNUM_WIDTH 1145.0f

// ���� ��ư L
#define LMSTATNUM_WIDTH 1067.0f
#define LMSTATNUM_HEIGHT 197.f

// ���� ��ư R
#define RMSTATUM_WIDTH 1196.0f

// ����
#define MSTATITV 93.0f


// ���� ���׷��̵�
#define STATUX_WIDTH 1002 // ��ġ��
#define STATUY_HEIGHT 160 // ��ġ��
#define STATUB_WIDTH 113 // ��ư����
#define STATUB_HEIGHT 42 // ��ư����
// ���� ���׷��̵� �ۼ�Ʈ
#define STATUPX_WIDTH 1131 // ��ġ��
#define STATP_HITV 50 // ���� �ۼ�Ʈ ���Ʒ� ���� ����




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
