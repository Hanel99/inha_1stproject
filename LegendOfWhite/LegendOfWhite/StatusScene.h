#pragma once
#include "Scene.h"

// ���� ��� �������ͽ� L
#define LSTATNUM_WIDTH 575
#define LSTATNUM_HEIGHT 168

// ���Ʒ� ����
#define STATITV 92

// ���� ��� �������ͽ� R
#define RSTATNUM_WIDTH 694


// ���� ��� �������ͽ� ��ȭ L
#define LSTATUPNUM_WIDTH 1016
#define LSTATUPNUM_HEIGHT 168

// ���� ��� �������ͽ� ��ȭ R
#define RSTATUPNUM_WIDTH 1145

// ���� ��ư L
#define LMSTATNUM_WIDTH 1067
#define LMSTATNUM_HEIGHT 197

// ���� ��ư R
#define RMSTATUM_WIDTH 1196

// ����
#define MSTATITV 93


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
	~StatusScene();

	virtual void Init()override;
	virtual void Update(float Delta)override;
	virtual void Release()override;
	virtual void Render(Gdiplus::Graphics* MemG)override;
	virtual void SendLButtonDown(UINT nFlags, CPoint point)override;
	virtual void SendRButtonDown(UINT nFlags, CPoint point)override;
	
	Gdiplus::PointF P;
	std::wstring tempStr;

	Player* player;

public:
	std::weak_ptr<Gdiplus::Image> statImg;
	std::weak_ptr<Gdiplus::Image> tabImg;
	std::weak_ptr<Gdiplus::Image> bgImg;
};
