#pragma once

enum EScene {
	eScene_Start,
	eScene_Game,
	eScene_Cnt
};

enum EObjectType
{
	eObjectType_None,
	eObjectType_Btn,
	eObjectType_Static,
	eObjectType_Player,
	eObjectType_Bullet,
	eObjectType_Enemy,
	eObjectType_Cnt,
	eObjectType_EnemyMissile
};
enum EAtlas
{
	eMissile = 1,
	ePlayer = 2,
	eEnemy = 3,
	eGameStart = 4,
	eGameEnd = 5,
	eEnemyMissile = 6
};
enum EState
{
	eIdle,
	eFail,
	eClear
};

class AtlasInfo
{
public:
	AtlasInfo()
	{

	}

	AtlasInfo(int _id, float _left, float _right, float _top, float _bottom)
		:id(_id),
		UV_Left(_left),
		UV_Right(_right),
		UV_Top(_top),
		UV_Bottom(_bottom)
	{

	}

public:
	int id;
	float UV_Left;
	float UV_Right;
	float UV_Top;
	float UV_Bottom;
};