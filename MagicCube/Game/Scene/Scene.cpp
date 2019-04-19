#include "Scene.h"

Scene::Scene(wstring sceneName)
{
	this->sceneName = sceneName;
}

Scene::~Scene()
{
	for (auto var : cameraList)
	{
		delete var;
	}
	for (auto var : actorMap)
	{
		delete var.second;
	}
}

Camera* Scene::CreateCamera()
{
	Camera* camera = new Camera();
	cameraList.push_back(camera);
	return camera;
}

void Scene::RenderSceneToCamera(Camera* camera)
{
	for (auto var : actorMap)
	{
		var.second->Render(camera->GetProjectMatrix(), camera->GetViewMatrix());
	}
}
