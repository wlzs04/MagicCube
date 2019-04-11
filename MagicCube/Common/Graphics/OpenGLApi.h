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
	Shader* LoadShader(string vertexShaderPath, string fragmentShaderPath) override;
	//Texture* LoadTexture(string texturePath) override;
	int CreateTextureSlot(int width, int height, int channelNumber, const void* data) override;
	int GetSprite(vector<float> vertices, vector<unsigned int> indices, vector<VertexAttribute> attributes, int numberEveryVertice) override;

	void DrawSprite(int id, int indicesNumber) override;

	void SetTexture(int textureIndex, Texture* texture) override;
private:
	OpenGLApi();
	~OpenGLApi() override;
	void Init() override;
};