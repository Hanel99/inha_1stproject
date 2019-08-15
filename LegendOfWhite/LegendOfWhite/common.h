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
	eObjectType_Wall,
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

enum EXMLType
{
	eXMLType_Btn,
	eXMLType_Obj,
	eXMLType_Cnt
};

enum EXMLObjnum
{
	eXMLObjnum_Wall_blue,
	eXMLObjnum_Wall_gray,
	eXMLObjnum_EBullet,
	eXMLObjnum_PBullet,
	eXMLObjnum_NextStage,
	eXMLObjnum_Ground,
	eXMLObjnum_pu2,
	eXMLObjnum_pu3,
	eXMLObjnum_pr1,
	eXMLObjnum_pr2,
	eXMLObjnum_pr3,
	eXMLObjnum_pl1,
	eXMLObjnum_pl2,
	eXMLObjnum_pl3,
	eXMLObjnum_pd1,
	eXMLObjnum_pd2,
	eXMLObjnum_pd3,
	eXMLObjnum_pu1,
	eXMLObjnum_Cnt
};