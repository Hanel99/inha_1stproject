#include "pch.h"
#include "GameData.h"

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

	ATKP = 5;
	ATKM = 0.0f;
	SSPDP = 1;
	SSPDM = 0.0f;
	SPDP = 1;
	SPDM = 0.0f;
	HP = 3;
	healCount = 0;
	CRI = 0.2f;

	SavePlayerData();

	LoadPlayerData();
	LoadSceneData();
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

		rst = sqlite3_exec(pSQLite3, (CStringA)temp.GetBuffer(), 0, 0, 0);
	}
	//객체해제 
	sqlite3_free(szErrMsg);
	sqlite3_close(pSQLite3);
}

int GameData::LoadSceneData()
{
	sqlite3* pSQLite3 = NULL;
	char* szErrMsg = NULL;
	sqlite3_stmt* stmt;
	int err = 0, cnt = 0;
	const char* tail;

	int rst = sqlite3_open("maindb.db", &pSQLite3);
	if (rst)
	{
		printf("Can't open database: %s\n", sqlite3_errmsg(pSQLite3));
		sqlite3_close(pSQLite3); pSQLite3 = NULL;
	}
	else
	{
		err = sqlite3_prepare_v2(pSQLite3, "SELECT * FROM scenedata", 1000, &stmt, &tail);

		if (err != SQLITE_OK) {
			printf("Select failed");
			return 0;
		}

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			dbSceneData = new DBSceneData;
			dbSceneData->datanum = sqlite3_column_int(stmt, 0); //datanum	
			dbSceneData->chapter = sqlite3_column_int(stmt, 1); //chapter
			dbSceneData->stage = sqlite3_column_int(stmt, 2); //stage
			dbSceneData->objtype = (EObjectType)sqlite3_column_int(stmt, 3); //objtype
			dbSceneData->x = sqlite3_column_int(stmt, 4); //x
			dbSceneData->y = sqlite3_column_int(stmt, 5); //y
			DBSceneVec.emplace_back(dbSceneData);
			cnt++;
		}
	}
	//객체해제 
	sqlite3_free(szErrMsg);
	sqlite3_close(pSQLite3);
}

int GameData::LoadPlayerData()
{
	sqlite3* pSQLite3 = NULL;
	char* szErrMsg = NULL;
	sqlite3_stmt* stmt;
	int err = 0, cnt = 0;
	const char* tail;

	int rst = sqlite3_open("maindb.db", &pSQLite3);
	if (rst)
	{
		printf("Can't open database: %s\n", sqlite3_errmsg(pSQLite3));
		sqlite3_close(pSQLite3); pSQLite3 = NULL;
	}
	else
	{
		err = sqlite3_prepare_v2(pSQLite3, "SELECT * FROM playerdata", 1000, &stmt, &tail);

		if (err != SQLITE_OK) {
			printf("Select failed");
			return 0;
		}

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			dbPlayerData.LV = sqlite3_column_int(stmt, 1); //Lv
			dbPlayerData.EXP = sqlite3_column_int(stmt, 2); //EXP
			dbPlayerData.skillPoint = sqlite3_column_int(stmt, 3); //skillPoint
			dbPlayerData.chapter = sqlite3_column_int(stmt, 4); //chapter
			dbPlayerData.stage = sqlite3_column_int(stmt, 5); //stage
			dbPlayerData.HP = sqlite3_column_int(stmt, 6); //HP
			dbPlayerData.ATKP = sqlite3_column_int(stmt, 7); //ATKP
			dbPlayerData.ATKM = sqlite3_column_double(stmt, 8); //ATKM
			dbPlayerData.SPDP = sqlite3_column_int(stmt, 9); //SPDP
			dbPlayerData.SPDM = sqlite3_column_double(stmt, 10); //SPDM
			dbPlayerData.SSPDP = sqlite3_column_int(stmt, 11); //SSPDP
			dbPlayerData.SSPDM = sqlite3_column_double(stmt, 12); //SSPDM
			dbPlayerData.CRI = sqlite3_column_double(stmt, 13); //CRI
			dbPlayerData.healCount = sqlite3_column_int(stmt, 14); //healCount
			cnt++;
		}
	}
	//객체해제 
	sqlite3_free(szErrMsg);
	sqlite3_close(pSQLite3);
}


DBSceneData* GameData::GetSceneData(int chapter, int stage)
{
	for (auto& it : DBSceneVec)
	{
		if (it->chapter == chapter && it->stage == stage)
			return it;
	}
	return nullptr;
}
