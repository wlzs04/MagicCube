#include "Shader.h"
#include <fstream> 
#include <sstream> 
#include "../../Manager/GraphicsManager.h"

void Shader::LoadShader(wstring vertexShaderPath, wstring fragmentShaderPath)
{
	this->vertexShaderPath = vertexShaderPath;
	this->fragmentShaderPath = fragmentShaderPath;

	shaderId = GraphicsManager::GetGraphicsApi()->CreateShaderSlot(vertexShaderPath, fragmentShaderPath);
}

void Shader::Use()
{
	GraphicsManager::GetGraphicsApi()->SetCurrentShader(shaderId);
}

int Shader::GetShaderId()
{
	return shaderId;
}