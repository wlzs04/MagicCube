#include "GraphicsManager.h"

GraphicsApi* GraphicsManager::graphicsApi = nullptr;

void GraphicsManager::Init()
{
}

void GraphicsManager::Clean()
{
	if (graphicsApi != nullptr)
	{
		delete graphicsApi;
		graphicsApi = nullptr;
	}
}

GraphicsApi* GraphicsManager::GetGraphicsApi()
{
	return graphicsApi;
}

void GraphicsManager::SetGraphicsApiType(GraphicsApiType graphicsApiType)
{
	switch (graphicsApiType)
	{
	case GraphicsApiType::Unknown:
		graphicsApi = nullptr;
		break;
	case GraphicsApiType::OpenGL:
		graphicsApi = new OpenGLApi();
		break;
	default:
		graphicsApi = nullptr;
		break;
	}
}
