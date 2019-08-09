#pragma once

enum EScene {
	eScene_Intro,
	eScene_Game,
	eScene_Cnt
};

enum EPlayerState {
	ePlayerState_PIdle,
	ePlayerState_PMoveL,
	ePlayerState_PMoveR,
	ePlayerState_PMoveU,
	ePlayerState_PMoveD,
	ePlayerState_Cnt
};

enum EEnemyState {
	eEnemyState_EMoveL,
	eEnemyState_EMoveR,
	eEnemyState_Cnt
};

enum EObjectType
{
	eObjectType_None,
	eObjectType_Object,
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