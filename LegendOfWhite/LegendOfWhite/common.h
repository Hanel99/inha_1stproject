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

enum EXMLBtnnum
{
	eXMLBtnnum_Newplay,
	eXMLBtnnum_Loadplay,
	eXMLBtnnum_Gameend,
	eXMLBtnnum_Newplayh,
	eXMLBtnnum_Loadplayh,
	eXMLBtnnum_Gameendh,
	eXMLBtnnum_Cnt
};

enum EXMLObjnum
{
	eXMLObjnum_Wall_blue,
	eXMLObjnum_Wall_gray,
	eXMLObjnum_EBullet,
	eXMLObjnum_PBullet,
	eXMLObjnum_NextStage,
	eXMLObjnum_Ground,
	eXMLObjnum_Pl1,
	eXMLObjnum_Pl2,
	eXMLObjnum_Pl3,
	eXMLObjnum_Pr1,
	eXMLObjnum_Pr2,
	eXMLObjnum_Pr3,
	eXMLObjnum_Pu1,
	eXMLObjnum_Pu2,
	eXMLObjnum_Pu3,
	eXMLObjnum_Pd1,
	eXMLObjnum_Pd2,
	eXMLObjnum_Pd3,
	eXMLObjnum_Cnt
};