#include "../../ThreeParty/glad/glad.h"
#include "../../ThreeParty/glfw/glfw3.h"

#include "OpenGLApi.h"
#include "../CommonHelper.h"

void OpenGLApi::SetViewPort(int width, int height)
{
	this->width = width;
	this->height = height;
	glViewport(0, 0, width, height);
}

void OpenGLApi::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}

void OpenGLApi::ClearViewPort()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

Shader* OpenGLApi::LoadShader(string vertexShaderPath, string fragmentShaderPath)
{
	shader = new Shader(vertexShaderPath, fragmentShaderPath);
	return shader;
}

Texture* OpenGLApi::LoadTexture(string texturePath)
{
	unsigned int texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	texture = new Texture(texture0);
	texture->LoadTexture(texturePath);
	if (texture->GetData() != nullptr)
	{
		if (texture->GetChannelNumber() == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->GetWidth(), texture->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture->GetData());
		}
		else if (texture->GetChannelNumber() == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->GetWidth(), texture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->GetData());
		}
		//自动配置多级渐远纹理
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	texture->ClearData();
	return texture;
}

Sprite* OpenGLApi::GetSprite(vector<float> vertices, vector<unsigned int> indices, vector<VertexAttribute> attributes, int numberEveryVertice)
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//float vertices[] = {
	//   0.5f, 0.5f, 0.0f, 1.0f, 1.0f,// 右上角
	//   0.5f, -0.5f, 0.0f, 1.0f, 0.0f,// 右下角
	//   -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // 左下角
	//   -0.5f, 0.5f, 0.0f, 0.0f, 1.0f // 左上角
	//};

	//unsigned int indices[] = {
	//0, 1, 3, // 第一个三角形
	//1, 2, 3  // 第二个三角形
	//};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()* sizeof(float), vertices.data(), GL_STATIC_DRAW);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	int startIndex = 0;
	int haveNumber = 0;
	for (int i = 0; i < attributes.size(); i++)
	{
		glVertexAttribPointer(startIndex, attributes[i].number, GL_FLOAT, GL_FALSE, numberEveryVertice * sizeof(float), (void*)(haveNumber * sizeof(float)));
		glEnableVertexAttribArray(startIndex);
		startIndex++;
		haveNumber += attributes[i].number;
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	sprite = new Sprite(VAO);
	sprite->SetIndicesNumber(CommonHelper::GetArrayLength(indices));
	return sprite;
}

void OpenGLApi::DrawSprite(Sprite* sprite)
{
	glBindVertexArray(sprite->GetSpriteId());
	glDrawElements(GL_TRIANGLES, sprite->GetIndicesNumber(), GL_UNSIGNED_INT, 0);
}

void OpenGLApi::SetTexture(int textureIndex,Texture* texture)
{
	//获得可用纹理数量上限
	int textureNumberLimit = 0;
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &textureNumberLimit);
	if (textureIndex < textureNumberLimit)
	{
		glActiveTexture(GL_TEXTURE0 + textureIndex);
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureId());
	}
	else
	{
		//警告
	}
}

OpenGLApi::OpenGLApi()
{
	graphicsApiType = GraphicsApiType::OpenGL;
	Init();
}

OpenGLApi::~OpenGLApi()
{
	if (shader != nullptr)
	{
		delete shader;
		shader = nullptr;
	}
	if (texture != nullptr)
	{
		delete texture;
		texture = nullptr;
	}
	if (sprite != nullptr)
	{
		delete sprite;
		sprite = nullptr;
	}
}

void OpenGLApi::Init()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return;
	}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}
