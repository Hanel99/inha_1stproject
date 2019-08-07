#pragma once

enum EScene {
	eScene_Start,
	eScene_Game,
	eScene_Cnt
};

enum EState {
	eState_Idle,
	eState_Move,
	eState_Cnt
};

enum EObjectType
{
	eObjectType_None,
	eObjectType_Btn,
	eObjectType_Static,
	eObjectType_Player,
	eObjectType_PBullet,
	eObjectType_Enemy,
	eObjectType_EBullet,
	eObjectType_NextStage,
	eObjectType_Cnt
};

enum EMonsterType
{
	eMonsterType_Bird,
	eMonsterType_Digda,
	eMonsterType_Devil,
	eMonsterType_Slime,
	eMonsterType_Cnt
};