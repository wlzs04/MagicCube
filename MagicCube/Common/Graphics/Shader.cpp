#include "Shader.h"
#include <fstream> 
#include <sstream> 
#include "../../Manager/GraphicsManager.h"
#include "../CommonHelper.h"

void Shader::LoadShaderFromPath(wstring vertexShaderPath, wstring fragmentShaderPath)
{
	this->vertexShaderPath = vertexShaderPath;
	this->fragmentShaderPath = fragmentShaderPath;
	wstring vertexShader = CommonHelper::LoadStringFromFile(vertexShaderPath);
	wstring fragmentShader = CommonHelper::LoadStringFromFile(fragmentShaderPath);
	shaderId = GraphicsManager::GetGraphicsApi()->CreateShaderSlotFromValue(vertexShader, fragmentShader);
}

void Shader::LoadShaderFromValue(wstring vertexShader, wstring fragmentShader)
{
	shaderId = GraphicsManager::GetGraphicsApi()->CreateShaderSlotFromValue(vertexShader, fragmentShader);
}

void Shader::Use()
{
	GraphicsManager::GetGraphicsApi()->SetCurrentShader(shaderId);
}

int Shader::GetShaderId()
{
	return shaderId;
}

wstring Shader::GetVectexShaderCommonValue()
{
	wstring vectorCommonShader=L"\
#version 330 core\n\
\n\
layout(location = 0) in vec3 position;\n\
layout(location = 1) in vec2 textureUV;\n\
\n\
out vec2 texCoord;\n\
\n\
@DefindSlot\n\
\n\
void main()\n\
{\n\
	texCoord = textureUV;\n\
@DefindFinalPosition\n\
}";
	return vectorCommonShader;
}

wstring Shader::GetFragmentShaderCommonValue()
{
	wstring fragmentCommonShader = L"\
#version 330 core\n\
\n\
in vec2 texCoord;\n\
out vec4 FragColor;\n\
\n\
@DefindSlot\n\
\n\
void main()\n\
{\n\
@DefinwFinalColor\n\
}";
	return fragmentCommonShader;
}
