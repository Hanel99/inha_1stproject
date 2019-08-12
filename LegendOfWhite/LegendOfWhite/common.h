#pragma once

enum EScene {
	eScene_Intro,
	eScene_Game,
	eScene_Status,
	eScene_Cnt
};

enum EPlayerState {
	ePlayerState_PIdle,
	ePlayerState_PMove,
	ePlayerState_Cnt
};

enum EEnemyState {
	eEnemyState_EMoveL,
	eEnemyState_EMoveR,
	eEnemyState_Cnt
};

enum EPlayerLook
{
	ePlayerLook_Left,
	ePlayerLook_Right,
	ePlayerLook_Up,
	ePlayerLook_Down
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

enum EEnemyType
{
	eEnemyType_Bird,
	eEnemyType_Digda,
	eEnemyType_Devil,
	eEnemyType_Slime,
	eEnemyType_Cnt
};