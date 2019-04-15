#pragma once
#include <vector>
#include <string>
#include <iostream>

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
	virtual int CreateShaderSlot(wstring vertexShaderPath, wstring pixelShaderPath) = 0;

	//设置当前着色器
	virtual void SetCurrentShader(int shaderId) = 0;

	virtual int GetShaderSlotIdByName(int shaderId,wstring name) = 0;

	//设置着色器传递参数
	virtual void SetBoolValueToShaderSlot(int slotId, bool value) = 0;
	virtual void SetIntValueToShaderSlot(int slotId, int value) = 0;
	virtual void SetFloatValueToShaderSlot(int slotId, float value) = 0;
	virtual void SetVector4ValueToShaderSlot(int slotId, float value0, float value1, float value2, float value3) = 0;
	virtual void SetMatrix4ValueToShaderSlot(int slotId, const float* value) = 0;

	//加载纹理
	virtual int CreateTextureSlot(int width, int height, int channelNumber,const void* data) = 0;

	//设置图形
	virtual int GetSprite(vector<float> vertices, vector<unsigned int> indices, vector<VertexAttribute> attributes, int numberEveryVertice) = 0;

	//设置矩形
	virtual void DrawSprite(int id, int indicesNumber) = 0;

	//设置纹理
	virtual void SetTexture(int textureIndex,int textureId) = 0;
protected:
	virtual ~GraphicsApi() {};
	//初始化
	virtual void Init() = 0;

	//图形渲染类型
	GraphicsApiType graphicsApiType = GraphicsApiType::Unknown;

	int width = 0;
	int height = 0;
};