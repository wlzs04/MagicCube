#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "Shader.h"
#include "Texture.h"

using namespace std;

//图形渲染类型
enum class GraphicsApiType
{
	Unknown,
	OpenGL,
};

//顶点属性
struct VertexAttribute
{
public :
	VertexAttribute(int newIndex,int newNumber)
	{
		index = newIndex;
		number = newNumber;
	}

	int index;//位置
	int number;//数量
};

//图形渲染Api基类(其他图形渲染Api需要继承该类)
class GraphicsApi
{
	friend class GraphicsManager;
public:
	//获得图形渲染类型
	GraphicsApiType GetGraphicsApiType();

	//设置视口大小
	virtual void SetViewPortSize(int width,int height) = 0;

	//设置清屏颜色
	virtual void SetClearColor(float r, float g, float b, float a) = 0;

	//清屏
	virtual void ClearViewPort() = 0;

	//加载着色器
	virtual Shader* LoadShader(string vertexShaderPath, string fragmentShaderPath) = 0;

	//加载纹理
	//virtual Texture* LoadTexture(string texturePath) = 0;
	virtual int CreateTextureSlot(int width, int height, int channelNumber,const void* data) = 0;

	//设置图形
	virtual int GetSprite(vector<float> vertices, vector<unsigned int> indices, vector<VertexAttribute> attributes, int numberEveryVertice) = 0;

	//设置矩形
	virtual void DrawSprite(int id, int indicesNumber) = 0;

	//设置纹理
	virtual void SetTexture(int textureIndex,Texture* texture) = 0;
protected:
	virtual ~GraphicsApi() {};
	//初始化
	virtual void Init() = 0;

	//图形渲染类型
	GraphicsApiType graphicsApiType = GraphicsApiType::Unknown;

	int width = 0;
	int height = 0;
};