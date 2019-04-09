#pragma once
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"

#include <string>
#include <iostream>

using namespace std;

//图形渲染类型
enum class GraphicsApiType
{
	Unknown,
	OpenGL,
};

//图形渲染Api基类(其他图形渲染Api需要继承该类)
class GraphicsApi
{
	friend class GraphicsManager;
public:
	//获得图形渲染类型
	GraphicsApiType GetGraphicsApiType();

	//设置视口大小
	virtual void SetViewPort(int width,int height) = 0;

	//设置清屏颜色
	virtual void SetClearColor(float r, float g, float b, float a) = 0;

	//清屏
	virtual void ClearViewPort() = 0;

	//加载着色器
	virtual Shader* LoadShader(string vertexShaderPath, string fragmentShaderPath) = 0;

	//加载纹理
	virtual Texture* LoadTexture(string texturePath) = 0;

	//设置矩形
	virtual Sprite* GetRectangle() = 0;

	//设置矩形
	virtual void DrawSprite(Sprite* sprite) = 0;

	//设置矩形
	virtual void SetCurrentTexture(Texture* texture) = 0;
protected:
	virtual ~GraphicsApi() {};
	//初始化
	virtual void Init() = 0;

	//图形渲染类型
	GraphicsApiType graphicsApiType = GraphicsApiType::Unknown;

	int width = 0;
	int height = 0;
};