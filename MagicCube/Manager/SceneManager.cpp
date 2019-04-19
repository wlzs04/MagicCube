#include "SceneManager.h"

SceneManager* SceneManager::sceneManager = nullptr;

void SceneManager::Init(wstring projectName)
{
	if (sceneManager == nullptr)
	{
		sceneManager = new SceneManager();
	}
	sceneManager->projectName = projectName;
}

void SceneManager::Clean()
{
	if (sceneManager != nullptr)
	{
		for (auto var : sceneManager->sceneMap)
		{
			delete var.second;
		}
		sceneManager->projectName = L"";
		sceneManager->currentScene = nullptr;
		delete sceneManager;
		sceneManager = nullptr;
	}
}

SceneManager* SceneManager::GetInstance()
{
	return sceneManager;
}

Scene* SceneManager::CreateScene(wstring sceneName)
{
	if (sceneMap.count(sceneName) > 0)
	{
		return sceneMap[sceneName];
	}
	else
	{
		Scene* scene = new Scene(sceneName);
		sceneMap[sceneName] = scene;
		return scene;
	}
}

Scene* SceneManager::LoadSceneFromFile(wstring filePath)
{
	return nullptr;
}

void SceneManager::SetCurrentScene(Scene* newCurrentScene)
{
	currentScene = newCurrentScene;
}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}
