#include "OpenGLApi.h"
#include "../../ThreeParty/glad/glad.h"
#include "../../ThreeParty/glfw/glfw3.h"

void OpenGLApi::SetViewPortSize(int width, int height)
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
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
}

Shader* OpenGLApi::LoadShader(string vertexShaderPath, string fragmentShaderPath)
{
	Shader* shader = new Shader(vertexShaderPath, fragmentShaderPath);
	return shader;
}

//Texture* OpenGLApi::LoadTexture(string texturePath)
//{
//	unsigned int texture0;
//	glGenTextures(1, &texture0);
//	glBindTexture(GL_TEXTURE_2D, texture0);
//	// 为当前绑定的纹理对象设置环绕、过滤方式
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	Texture* texture = new Texture(texture0);
//	texture->LoadTexture(texturePath);
//	if (texture->GetData() != nullptr)
//	{
//		if (texture->GetChannelNumber() == 3)
//		{
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->GetWidth(), texture->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, texture->GetData());
//		}
//		else if (texture->GetChannelNumber() == 4)
//		{
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->GetWidth(), texture->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->GetData());
//		}
//		//自动配置多级渐远纹理
//		glGenerateMipmap(GL_TEXTURE_2D);
//	}
//	texture->ClearData();
//	return texture;
//}

int OpenGLApi::CreateTextureSlot(int width, int height, int channelNumber, const void* data)
{
	unsigned int texture0;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (channelNumber == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else if (channelNumber == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	//自动配置多级渐远纹理
	glGenerateMipmap(GL_TEXTURE_2D);
	return texture0;
}

int OpenGLApi::GetSprite(vector<float> vertices, vector<unsigned int> indices, vector<VertexAttribute> attributes, int numberEveryVertice)
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

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

	return VAO;
}

void OpenGLApi::DrawSprite(int id,int indicesNumber)
{
	glBindVertexArray(id);
	glDrawElements(GL_TRIANGLES, indicesNumber, GL_UNSIGNED_INT, 0);
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
}

void OpenGLApi::Init()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}
