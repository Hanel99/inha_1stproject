#pragma once

enum EScene
{
	eScene_Intro,
	eScene_Game,
	eScene_Status,
	eScene_Cnt
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
	eObjectType_None = 0,
	eObjectType_Wall = 1,
	eObjectType_Player = 2,
	eObjectType_PBullet = 3,
	eObjectType_Enemy = 4,
	eObjectType_EBullet = 5,
	eObjectType_NextStage = 6,
	eObjectType_Cnt = 7
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