#pragma once


class Scene
{
public:
	void Start();
	void Loop(float Delta);
	void End();
	bool bLoop;
	CString Name;	
};

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	void LoadScene(CString& pName);
	void RenderScene(CDC* pDC);
	Scene* GetCurScene();
	void SendLButtonDown(UINT nFlags, CPoint point);
	void Update(float Delta);

private:
	std::vector<Scene*> mScene;
	Scene* CurScene;
};

SceneManager* SceneManager::instance = nullptr;