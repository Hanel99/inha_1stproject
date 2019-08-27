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

	ATKP = 1;
	ATKM = 0.0f;
	SSPDP = 1;
	SSPDM = 0.0f;
	SPDP = 1;
	SPDM = 0.0f;
	MAXHP = 3;
	player->HP = 3;
	healCount = 0;
	CRI = 0.0f;
	
	LoadPlayerData();
	LoadSceneData(TEXT(""));
}


void GameData::SavePlayerData()
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
		CString temp;
		temp.Format(TEXT("UPDATE playerdata SET LV = %d, EXP = %d, skillPoint = %d, chapter = %d, stage = %d, MAXHP = %d,playerHP = %d, ATKP = %d, ATKM = %f, SPDP = %d, SPDM = %f, SSPDP = %d, SSPDM = %f, CRI = %f, healCount = %d  WHERE datanum = 1")
			, player->LV, player->EXP, player->skillPoint, chapternum, stagenum, MAXHP, player->HP, ATKP, ATKM, SPDP, SPDM, SSPDP, SSPDM, CRI, healCount);

		rst = sqlite3_exec(pSQLite3, (CStringA)temp.GetBuffer(), 0, 0, 0);
	}
	sqlite3_free(szErrMsg);
	sqlite3_close(pSQLite3);
}

void GameData::SaveFirstPlayerData()
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
		CString temp;
		temp.Format(TEXT("UPDATE playerdata SET LV = %d, EXP = %d, skillPoint = %d, chapter = %d, stage = %d, MAXHP = %d, playerHP = %d, ATKP = %d, ATKM = %f, SPDP = %d, SPDM = %f, SSPDP = %d, SSPDM = %f, CRI = %f, healCount = %d  WHERE datanum = 1")
			, 1, 0, 0, 1, 1, 3, 3, 1, 0.0f, 1, 0.0f, 1, 0.0f, 0.0f, 0);

		rst = sqlite3_exec(pSQLite3, (CStringA)temp.GetBuffer(), 0, 0, 0);
	}
	sqlite3_free(szErrMsg);
	sqlite3_close(pSQLite3);
}

int GameData::LoadSceneData(CString where)
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
		CString temp = TEXT("SELECT * FROM scenedata ");
		temp.Append(where);
		err = sqlite3_prepare_v2(pSQLite3, (CStringA)temp.GetBuffer(), 1000, &stmt, &tail);

		if (err != SQLITE_OK) {
			printf("Select failed");
			return 0;
		}

		while (sqlite3_step(stmt) == SQLITE_ROW) {
			dbSceneData = new DBSceneData;
			dbSceneData->datanum = sqlite3_column_int(stmt, 0); //datanum	
			dbSceneData->chapter = sqlite3_column_int(stmt, 1); //chapter
			dbSceneData->stage = sqlite3_column_int(stmt, 2); //stage
			dbSceneData->enemytype = (EEnemyType)sqlite3_column_int(stmt, 3); //enemytype
			dbSceneData->x = sqlite3_column_int(stmt, 4); //x
			dbSceneData->y = sqlite3_column_int(stmt, 5); //y
			DBSceneVec.emplace_back(dbSceneData);
			cnt++;
		}
	}
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
			dbPlayerData.MAXHP = sqlite3_column_int(stmt, 6); //MAXHP
			dbPlayerData.playerHP = sqlite3_column_int(stmt, 7); //playerHP
			dbPlayerData.ATKP = sqlite3_column_int(stmt, 8); //ATKP
			dbPlayerData.ATKM = sqlite3_column_double(stmt, 9); //ATKM
			dbPlayerData.SPDP = sqlite3_column_int(stmt, 10); //SPDP
			dbPlayerData.SPDM = sqlite3_column_double(stmt, 11); //SPDM
			dbPlayerData.SSPDP = sqlite3_column_int(stmt, 12); //SSPDP
			dbPlayerData.SSPDM = sqlite3_column_double(stmt, 13); //SSPDM
			dbPlayerData.CRI = sqlite3_column_double(stmt, 14); //CRI
			dbPlayerData.healCount = sqlite3_column_int(stmt, 15); //healCount
			cnt++;
		}
	}
	sqlite3_free(szErrMsg);
	sqlite3_close(pSQLite3);
}

void GameData::SetPlayerDBData()
{
	player->LV = dbPlayerData.LV;
	player->EXP = dbPlayerData.EXP;
	player->skillPoint = dbPlayerData.skillPoint;
	chapternum = dbPlayerData.chapter;
	stagenum = dbPlayerData.stage;

	MAXHP = dbPlayerData.MAXHP;
	player->HP = dbPlayerData.playerHP;

	ATKP = dbPlayerData.ATKP;
	ATKM = dbPlayerData.ATKM;
	SPDP = dbPlayerData.SPDP;
	SPDM = dbPlayerData.SPDM;
	SSPDP = dbPlayerData.SSPDP;
	SSPDM = dbPlayerData.SSPDM;
	CRI = dbPlayerData.CRI;
	healCount = dbPlayerData.healCount;

	player->ATK = (player->LV + ATKP) * (1 + ATKM);
	player->SPD = 500 + (SPDP * (1 + SPDM) * 1.5f);
	player->SSPD = 800 + (SSPDP * (1 + SSPDM) * 3.0f);
	player->CRI = CRI;
}