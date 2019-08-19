#pragma once
#include "Scene.h"

// ����
#define STATX_WIDTH 560 // ��ġ��
#define STATY_HEIGHT 155 // ��ġ��
#define STAT_WIDTH 100 // ���̰�
#define STAT_HEIGHT 53 // ���̰�

// �ۼ�Ʈ ����
#define STATPX_WIDTH 680 // ��ġ��
#define STATPY_HEIGHT 160 // ��ġ��
#define STATP_WIDTH 113 // ���̰�
#define STATP_HEIGHT 42 // ���̰�

// ���� ����
#define STAT_HITV 39 // ���� ���Ʒ� ���� ����
#define STATP_HITV 50 // ���� �ۼ�Ʈ ���Ʒ� ���� ����
#define MINISTAT_HITV 65 // ���� ���� ���� ��ư ���Ʒ� ���� ����

// ���� ���׷��̵�
#define STATUX_WIDTH 1002 // ��ġ��
#define STATUY_HEIGHT 160 // ��ġ��

// ���� ���׷��̵� �ۼ�Ʈ
#define STATUPX_WIDTH 1131 // ��ġ��

// ���� ���� ���� ��ư
#define LMINISTATX_WIDTH 1058 // ��ġ��
#define LMINISTATY_HEIGHT 192 // ��ġ��
#define LMINISTAT_WIDTH 66 // ���̰�
#define LMINISTAT_HEIGHT 28 // ���̰�

// ������ ���� ���� ��ư
#define RMINISTATX_WIDTH 1187 // ��ġ��


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
