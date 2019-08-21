#include "pch.h"
#include "GameData.h"




static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	int i;
	for (i = 0; i < argc; i++)
	{
		if (GameData::GetInstance()->isPlayerData) //playerdata 이용중
		{
			switch (i)
			{
			case 1:
				GameData::GetInstance()->dbPlayerData.LV = atoi(argv[i]);
				//float f = atof(argv[i]);
				break;
			case 2:
				GameData::GetInstance()->dbPlayerData.EXP = atoi(argv[i]);
				break;
			case 3:
				GameData::GetInstance()->dbPlayerData.skillPoint = atoi(argv[i]);
				break;
			case 4:
				GameData::GetInstance()->dbPlayerData.chapter = atoi(argv[i]);
				break;
			case 5:
				GameData::GetInstance()->dbPlayerData.stage = atoi(argv[i]);
				break;
			case 6:
				GameData::GetInstance()->dbPlayerData.HP = atoi(argv[i]);
				break;
			case 7:
				GameData::GetInstance()->dbPlayerData.ATKP = atoi(argv[i]);
				break;
			case 8:
				GameData::GetInstance()->dbPlayerData.ATKM = atof(argv[i]);
				break;
			case 9:
				GameData::GetInstance()->dbPlayerData.SPDP = atoi(argv[i]);
				break;
			case 10:
				GameData::GetInstance()->dbPlayerData.SPDM = atof(argv[i]);
				break;
			case 11:
				GameData::GetInstance()->dbPlayerData.SSPDP = atoi(argv[i]);
				break;
			case 12:
				GameData::GetInstance()->dbPlayerData.SSPDM = atof(argv[i]);
				break;
			case 13:
				GameData::GetInstance()->dbPlayerData.CRI = atof(argv[i]);
				break;
			case 14:
				GameData::GetInstance()->dbPlayerData.healCount = atoi(argv[i]);
				break;

			default:
				break;
			}

		}
		else //scenedata 이용중
		{

			switch (i)
			{
			case 1:
				GameData::GetInstance()->dbSceneData->chapter = atoi(argv[i]);
				break;
			case 2:
				GameData::GetInstance()->dbSceneData->stage = atoi(argv[i]);
				break;
			case 3:
				GameData::GetInstance()->dbSceneData->objtype = (EObjectType)atoi(argv[i]);
				break;
			case 4:
				GameData::GetInstance()->dbSceneData->x = atoi(argv[i]);
				break;
			case 5:
				GameData::GetInstance()->dbSceneData->y = atoi(argv[i]);
				break;

			default:
				break;
			}
		}
	}
	if (!GameData::GetInstance()->isPlayerData)
	{
		GameData::GetInstance()->DBSceneVec.emplace_back(GameData::GetInstance()->dbSceneData);
	}

	return 0;
};




GameData::GameData()
	: stagenum(1)
	, chapternum(1)
{
	Init();
}

GameData::~GameData()
{
}

void GameData::Init()
{
	player = new Player;
	//이어하기를 눌렀을경우, DB불러서 데이터 가져오기
	//새로시작의 경우 위 DB불러오는걸 넘기고 초기값 셋팅해준뒤 바로 게임씬으로 이동.

	ATKP = 1;
	ATKM = 0.0f;
	SSPDP = 1;
	SSPDM = 0.0f;
	SPDP = 1;
	SPDM = 0.0f;
	HP = 3;
	healCount = 0;
	CRI = 0.0f;

	
}

int GameData::GetStagenum()
{
	return stagenum;
}

void GameData::SetStagenum(int stage)
{
	stagenum = stage;
}

int GameData::GetChapternum()
{
	return chapternum;
}

void GameData::SetChapternum(int chapter)
{
	chapternum = chapter;
}

void GameData::SavePlayerData()
{
	sqlite3* pSQLite3 = NULL;
	// SQLite DB 객체저장변수
	char* szErrMsg = NULL;
	// Error 발생시메세지를저장하는변수

	// 데이터베이스열기: 파일이존재하지않으면생성한다. 
	int rst = sqlite3_open("maindb.db", &pSQLite3);
	if (rst)
	{
		printf("Can't open database: %s\n", sqlite3_errmsg(pSQLite3));
		sqlite3_close(pSQLite3); pSQLite3 = NULL;
	}
	else
	{
		CString temp;
		temp.Format(TEXT("UPDATE playerdata SET LV = %d, EXP = %d, skillPoint = %d, chapter = %d, stage = %d, HP = %d, ATKP = %d, ATKM = %f, SPDP = %d, SPDM = %f, SSPDP = %d, SSPDM = %f, CRI = %f, healCount = %d  WHERE datanum = 1")
			, player->LV, player->EXP, player->skillPoint, chapternum, stagenum, player->HP, ATKP, ATKM, SPDP, SPDM, SSPDP, SSPDM, CRI, healCount);
		
		isPlayerData = true;
		//이거 계속 에러남... 유니코드 뭐시기 문제라고도 하고
		//rst = sqlite3_exec(pSQLite3, temp.GetBuffer(), 0, 0, 0);
	}
	//객체해제 
	sqlite3_free(szErrMsg);
	sqlite3_close(pSQLite3);
}

void GameData::LoadSceneData()
{
	sqlite3* pSQLite3 = NULL;
	char* szErrMsg = NULL;

	int rst = sqlite3_open("maindb.db", &pSQLite3);
	if (rst)
	{
		printf("Can't open database: %s\n", sqlite3_errmsg(pSQLite3));
		sqlite3_close(pSQLite3); pSQLite3 = NULL;
	}
	else
	{
		isPlayerData = false;
		rst = sqlite3_exec(pSQLite3, "SELECT * FROM scenedata", callback, 0, &szErrMsg);
	}
	//객체해제 
	sqlite3_free(szErrMsg);
	sqlite3_close(pSQLite3);
}

void GameData::LoadPlayerData()
{
	sqlite3* pSQLite3 = NULL;
	char* szErrMsg = NULL;

	int rst = sqlite3_open("maindb.db", &pSQLite3);
	if (rst)
	{
		printf("Can't open database: %s\n", sqlite3_errmsg(pSQLite3));
		sqlite3_close(pSQLite3); pSQLite3 = NULL;
	}
	else
	{
		isPlayerData = true;
		rst = sqlite3_exec(pSQLite3, "SELECT * FROM playerdata", callback, 0, &szErrMsg);
	}
	//객체해제 
	sqlite3_free(szErrMsg);
	sqlite3_close(pSQLite3);
}


DBSceneData* GameData::GetSceneData(int chapter, int stage)
{
	for (auto& it : DBSceneVec)
	{
		if(it->chapter == chapter && it->stage == stage)
			return it;
	}
	return nullptr;
}

