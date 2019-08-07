#include "pch.h"
#include "SceneManager.h"

void Btn::SendLButtonDown()
{
	switch (ID)
	{
	case 0:
		SceneManager::GetInstance().LoadScene(CString("Scene_Game"));
		break;
	case 1:
		PostQuitMessage(0);
		break;
	}
}

void Scene::Start()
{
	bLoop = false;

	///////////////
	//info 채우는 부분
	bLoop = true;
}

void Scene::Loop(float Delta)
{
	if (!bLoop) return;

}

void Scene::End()
{
	bLoop = false;
	
	/*	
	for (auto& it : info)
	{
		delete it;
		it = nullptr;
	}

	info.empty();
	*/
}


SceneManager& SceneManager::GetInstance()
{
	static SceneManager cm;
	return cm;
}

SceneManager::SceneManager()
	: CurScene(nullptr)
{
	
	Scene* LoginScene = new Scene();
	Scene* GameScene = new Scene();

	/*
	Btn* n1 = new Btn();
	Btn* n2 = new Btn();

	CImage* cm = new CImage();
	cm->Load(TEXT("Asset\\ed.jpg"));

	n1->ParentImg = cm;
	n2->ParentImg = cm;

	n1->ID = 0;
	n2->ID = 1;
	n1->Img.Create(100, 100, cm->GetBPP());
	n2->Img.Create(100, 100, cm->GetBPP());
	::StretchBlt(n1->Img.GetDC(), 0, 0, 100, 100, cm->GetDC(), 10, 10, 30, 30, SRCCOPY);
	::StretchBlt(n2->Img.GetDC(), 0, 0, 100, 100, cm->GetDC(), 10, 40, 30, 30, SRCCOPY);

	n1->rc = CRect(100, 100, 200, 150);
	n2->rc = CRect(100, 300, 200, 350);


	StaticObject* bg = new StaticObject();
	Player* player = new Player();
	Enemy* enemy1 = new Enemy();
	Enemy* enemy2 = new Enemy();
	Enemy* enemy3 = new Enemy();

	CImage* bgImg = new CImage();
	bgImg->Load(TEXT("Asset\\bg.png"));

	bg->ParentImg = bgImg;
	player->ParentImg = cm;
	player->temp.ParentImg = cm;

	bg->Img.Create(1080, 1920, cm->GetBPP());
	player->Img.Create(300, 400, cm->GetBPP());
	enemy1->Img.Create(300, 400, cm->GetBPP());
	enemy2->Img.Create(300, 400, cm->GetBPP());
	enemy3->Img.Create(300, 400, cm->GetBPP());
	player->temp.Img.Create(300, 400, cm->GetBPP());

	::StretchBlt(bg->Img.GetDC(), 0, 0, bgImg->GetWidth(), bgImg->GetHeight(), bgImg->GetDC(), 0, 0, bgImg->GetWidth(), bgImg->GetHeight(), SRCCOPY);
	::StretchBlt(player->Img.GetDC(), 0, 0, 300, 400, cm->GetDC(), 600, 800, 300, 400, SRCCOPY);
	::StretchBlt(player->temp.Img.GetDC(), 0, 0, 300, 400, cm->GetDC(), 600, 800, 300, 400, SRCCOPY);

	::StretchBlt(enemy1->Img.GetDC(), 0, 0, 300, 400, cm->GetDC(), 600, 800, 300, 400, SRCCOPY);
	::StretchBlt(enemy2->Img.GetDC(), 0, 0, 300, 400, cm->GetDC(), 600, 800, 300, 400, SRCCOPY);
	::StretchBlt(enemy3->Img.GetDC(), 0, 0, 300, 400, cm->GetDC(), 600, 800, 300, 400, SRCCOPY);

	bg->rc = CRect(0, -1080, 1080, 1920);
	player->rc = CRect(50, 300, 100, 350);

	enemy1->rc = CRect(0, -1500, 100, -1400);
	enemy2->rc = CRect(100, -1500, 200, -1400);
	enemy3->rc = CRect(200, -1500, 300, -1400);

	player->temp.rc = CRect(0, 0, 25, 25);

	GameScene->info.emplace_back(bg);
	GameScene->info.emplace_back(player);
	GameScene->info.emplace_back(enemy1);
	GameScene->info.emplace_back(enemy2);
	GameScene->info.emplace_back(enemy3);

	LoginScene->info.emplace_back(n1);
	LoginScene->info.emplace_back(n2);

	*/

	LoginScene->Name = "Scene_Start";
	GameScene->Name = "Scene_Game";

	mScene.emplace_back(LoginScene);
	mScene.emplace_back(GameScene);

}


void SceneManager::LoadScene(CString& pName)
{
	for (auto& it : mScene)
	{
		if (!it->Name.CompareNoCase(pName))
		{
			CurScene = it;
		}
	}

	//CurScene = nullptr;
}

/*
void SceneManager::RenderScene(CDC* pDC)
{
	if (CurScene == nullptr) return;
	if (pDC == nullptr) return;

	for (auto& it : CurScene->info)
	{
		if (it == nullptr) continue;
		if (it->Enable == false) continue;

		it->Img.Draw(pDC->GetSafeHdc(), it->rc);
	}
}

Scene* SceneManager::GetCurScene()
{
	return CurScene;
}

void SceneManager::SendLButtonDown(UINT nFlags, CPoint point)
{
	if (CurScene == nullptr) return;

	for (auto& it : CurScene->info)
	{
		if (it->Objtype == eObjectType_Btn && it->rc.PtInRect(point))
		{
			Btn* o = reinterpret_cast<Btn*>(it);
			o->SendLButtonDown();
		}
	}
}

void SceneManager::Update(float Delta)
{
	if (CurScene == nullptr) return;

	std::vector<Enemy*> enemyVec;
	int nSize = CurScene->info.size();
	for (int i = 0; i < nSize; ++i)
	{
		if (CurScene->info[i]->Enable == false) continue;

		if (CurScene->info[i]->Objtype == eObjectType_Enemy)
		{
			enemyVec.emplace_back(static_cast<Enemy*>(CurScene->info[i]));
		}
	}

	int nCnt = CurScene->info.size();
	for (auto it = 0; it < nCnt; ++it)
	{
		if (CurScene->info[it] == nullptr) continue;
		if (CurScene->info[it]->Enable == false) continue;

		CurScene->info[it]->Update(Delta);

		if (CurScene->info[it]->Objtype == eObjectType_Bullet)
		{
			Bullet* c = static_cast<Bullet*>((CurScene->info[it]));
			if (c->IsCullBull(enemyVec))
			{
				CurScene->info[it]->Enable = false;
			}
		}
	}
}

*/