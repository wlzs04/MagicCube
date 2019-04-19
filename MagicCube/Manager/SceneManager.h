#pragma once
#include <unordered_map>
#include "../Game/Scene/Scene.h"

class SceneManager
{
public:
	static void Init(wstring projectName);
	static void Clean();

	static SceneManager* GetInstance();

	Scene* CreateScene(wstring sceneName);
	Scene* LoadSceneFromFile(wstring filePath);

	void SetCurrentScene(Scene* newCurrentScene);
	Scene* GetCurrentScene();

private:
	SceneManager() {};
	~SceneManager() {};

	static SceneManager* sceneManager;
	Scene* currentScene = nullptr;
	unordered_map<wstring, Scene*> sceneMap;
	wstring projectName = L"";
};