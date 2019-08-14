#include "pch.h"
#include "GameScene.h"

GameScene::GameScene()
{
	Init();
}


void GameScene::Init()
{
	player = GameData::GetInstance()->player;
	SetStartPos(100, 100);

	enemy = new Enemy();

	//�̰� �̷��� �ϸ� �ȵǰ� �׸��� ������ �ش翵�� �׸��� �س�����
	for (int yy = 0; yy < HEIGHT; yy += 80)
	{
		wallVec.emplace_back(new Wall(0, yy));
		wallVec.emplace_back(new Wall(WIDTH-80, yy));
	}
	for (int xx = 0; xx < WIDTH; xx += 80)
	{
		wallVec.emplace_back(new Wall(xx, 0));
		wallVec.emplace_back(new Wall(xx, HEIGHT-80));
	}	

	objectVec.emplace_back(player);
	objectVec.emplace_back(enemy);	
}

void GameScene::Update(float Delta)
{
	//����â����
	if (GetAsyncKeyState(VK_TAB) & 0x1001)
	{
		SceneManager::GetInstance()->SwapStatusScene();
	}
	for (auto& it : objectVec)
	{
		it->Update(Delta);
	}
	for (auto& it : bulletVec)
	{
		it->Update(Delta);
		
		if (it->GetX() > WIDTH || it->GetX() < 0 || it->GetY() > HEIGHT || it->GetY() < 0)
		{
			//������Ʈ���Ϳ��� ���� ���� �׸���Ų������ ���¸Ŵ��� �Ҹ����Ϳ� �ٽ� �־������
			//ReturnBulletFromGameScene(it);
			AssetManager::GetInstance()->RetrunBullet(it);
		}
	}
}

void GameScene::Render(Gdiplus::Graphics* MemG)
{
	Gdiplus::Rect rect(0, 0, WIDTH, HEIGHT);

	Gdiplus::Bitmap bm(WIDTH, HEIGHT, PixelFormat32bppARGB);
	Gdiplus::Graphics temp(&bm);

	bgImg = AssetManager::GetInstance()->GetImage(TEXT("Asset\\bgImg.png"));

	temp.DrawImage(bgImg.lock().get(),
		rect, 0, 0, WIDTH, HEIGHT, Gdiplus::Unit::UnitPixel, nullptr, 0, nullptr);

	//�׷��� screen��ǥ�� rect
	Gdiplus::Rect screenPosRect(0, 0, WIDTH, HEIGHT);

	MemG->DrawImage(&bm, screenPosRect);

	for (auto& it : wallVec)
	{
		it->Render(MemG);
	}
	for (auto& it : bulletVec)
	{
		it->Render(MemG);
	}
	for (auto& it : objectVec)
	{
		it->Render(MemG);
	}	
}

void GameScene::SetStartPos(float x, float y)
{ 
	player->SetX(x);
	player->SetY(y);
}

void GameScene::SendLButtonDown(UINT nFlags, CPoint point)
{
	//Bullet* b = new Bullet(player->GetX() + player->width / 2, player->GetY() + player->height / 2, point.x + (i * 20), point.y+(i * 20));
	
	//for (int i = 0; i < 20; ++i)
	//{
	//	Bullet* b = AssetManager::GetInstance()->CreateBullet();
	//	if (b != nullptr)
	//	{
	//		b->BulletInit(player->GetX() + player->width / 2, player->GetY() + player->height / 2, point.x + (i * 20), point.y + (i * 20));
	//		bulletVec.emplace_back(b);
	//	}
	//}

	Bullet* b = AssetManager::GetInstance()->CreateBullet();
	if (b != nullptr)
	{
		b->BulletInit(player->GetX() + (player->width / 2), player->GetY() + (player->height / 2), point.x, point.y);
		bulletVec.emplace_back(b);
	}
}

void GameScene::ReturnBulletFromGameScene(Bullet* b)
{
	std::vector<Bullet*>::iterator it = std::find(bulletVec.begin(), bulletVec.end(), b);
	bulletVec.erase(it);
}



