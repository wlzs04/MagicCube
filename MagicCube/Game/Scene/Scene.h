#pragma once
#include <string>
#include <unordered_map>
#include "../Actor/Actor.h"
#include "../../Common/Graphics/Camera.h"

using namespace std;

class Scene
{
	friend class SceneManager;
public:
	template<class T>
	T* CreateActor(wstring actorName)
	{
		if (actorMap.count(actorName) > 0)
		{
			return (T*)actorMap[actorName];
		}
		else
		{
			T* actor = new T(actorName);
			actorMap[actorName] = actor;
			return actor;
		}
	}
	Camera* CreateCamera();

	//渲染场景到指定摄像机中
	void RenderSceneToCamera(Camera* camera);
private:
	Scene(wstring sceneName);
	~Scene();

	wstring sceneName;
	unordered_map<wstring, Actor*> actorMap;
	vector<Camera*> cameraList;
};