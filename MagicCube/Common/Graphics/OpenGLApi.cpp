#include "OpenGLApi.h"
#include "../CommonHelper.h"
#include "../WStringHelper.h"
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

int OpenGLApi::CreateShaderSlot(wstring vertexShaderPath, wstring pixelShaderPath)
{
	//加载顶点着色器
	wstring vertexShaderString = CommonHelper::LoadStringFromFile(vertexShaderPath);
	string aVertexShaderString = WStringHelper::WStringToString(vertexShaderString);
	const char* vertexShaderChar = aVertexShaderString.c_str();
	
	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderChar, NULL);
	glCompileShader(vertexShaderId);
	
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		//输出错误
		return 0;
	};

	//加载像素着色器
	wstring pixelShaderString = CommonHelper::LoadStringFromFile(pixelShaderPath);
	string aPixelShaderString = WStringHelper::WStringToString(pixelShaderString);
	const char* pixelShaderChar = aPixelShaderString.c_str();
	unsigned int pixelShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(pixelShaderId, 1, &pixelShaderChar, NULL);
	glCompileShader(pixelShaderId);

	glGetShaderiv(pixelShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(pixelShaderId, 512, NULL, infoLog);
		//输出错误
		return 0;
	};

	//合并
	unsigned int shaderProgramId = glCreateProgram();
	glAttachShader(shaderProgramId, vertexShaderId);
	glAttachShader(shaderProgramId, pixelShaderId);
	glLinkProgram(shaderProgramId);

	glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramId, 512, NULL, infoLog);
		//输出错误
		return 0;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(pixelShaderId);

	return shaderProgramId;
}

void OpenGLApi::SetCurrentShader(int shaderId)
{
	glUseProgram(shaderId);
}

int OpenGLApi::GetShaderSlotIdByName(int shaderId, wstring name)
{
	string aName = WStringHelper::WStringToString(name);
	return glGetUniformLocation(shaderId, aName.c_str());
}

void OpenGLApi::SetBoolValueToShaderSlot(int slotId, bool value)
{
	glUniform1i(slotId, (int)value);
}

void OpenGLApi::SetIntValueToShaderSlot(int slotId, int value)
{
	glUniform1i(slotId, value);
}

void OpenGLApi::SetFloatValueToShaderSlot(int slotId, float value)
{
	glUniform1f(slotId, value);
}

void OpenGLApi::SetVector4ValueToShaderSlot(int slotId, float value0, float value1, float value2, float value3)
{
	glUniform4f(slotId, value0, value1, value2, value3);
}

void OpenGLApi::SetMatrix4ValueToShaderSlot(int slotId, const float* value)
{
	glUniformMatrix4fv(slotId, 1, GL_FALSE, value);
}

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

void OpenGLApi::SetTexture(int textureIndex, int textureId)
{
	//获得可用纹理数量上限
	int textureNumberLimit = 0;
	glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &textureNumberLimit);
	if (textureIndex < textureNumberLimit)
	{
		glActiveTexture(GL_TEXTURE0 + textureIndex);
		glBindTexture(GL_TEXTURE_2D, textureId);
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