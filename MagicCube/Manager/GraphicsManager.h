#pragma once
#include "../Common/Graphics/OpenGLApi.h"

//图形管理器
class GraphicsManager
{
public:
	static void Init();
	static void Clean();

	//获得当前图形渲染Api实例
	static GraphicsApi* GetGraphicsApi();

	//设置当前图形渲染Api实例
	static void SetGraphicsApiType(GraphicsApiType graphicsApiType);
private:
	GraphicsManager();
	~GraphicsManager();

	//图形渲染Api实例
	static GraphicsApi* graphicsApi;
};