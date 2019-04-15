#pragma once
#include <vector>
#include "GraphicsApi.h"

#pragma comment(lib, "opengl32.lib") 

using namespace std;

//图形渲染Api：OpenGL
class OpenGLApi : public GraphicsApi
{
	friend class GraphicsManager;
public:
	void SetViewPortSize(int width, int height) override;
	void SetClearColor(float r, float g, float b, float a) override;
	void ClearViewPort() override;
	int CreateShaderSlot(wstring vertexShaderPath, wstring pixelShaderPath) override;
	void SetCurrentShader(int shaderId) override;
	int GetShaderSlotIdByName(int shaderId, wstring name) override;
	void SetBoolValueToShaderSlot(int slotId, bool value) override;
	void SetIntValueToShaderSlot(int slotId, int value) override;
	void SetFloatValueToShaderSlot(int slotId, float value) override;
	void SetVector4ValueToShaderSlot(int slotId, float value0, float value1, float value2, float value3) override;
	void SetMatrix4ValueToShaderSlot(int slotId, const float* value) override;
	int CreateTextureSlot(int width, int height, int channelNumber, const void* data) override;
	int GetSprite(vector<float> vertices, vector<unsigned int> indices, vector<VertexAttribute> attributes, int numberEveryVertice) override;

	void DrawSprite(int id, int indicesNumber) override;

	void SetTexture(int textureIndex, int textureId) override;
private:
	OpenGLApi();
	~OpenGLApi() override;
	void Init() override;
};