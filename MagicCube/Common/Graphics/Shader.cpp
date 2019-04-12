#include "Shader.h"
#include "../../ThreeParty/GLAD/glad.h"

#include <fstream> 
#include <sstream> 
#include "../CommonHelper.h"
#include "../../Manager/GraphicsManager.h"

void Shader::LoadShader(string vertexShaderPath, string fragmentShaderPath)
{
	this->vertexShaderPath = vertexShaderPath;
	this->fragmentShaderPath = fragmentShaderPath;

	shaderId = GraphicsManager::GetGraphicsApi()->CreateShaderSlot(vertexShaderPath, fragmentShaderPath);
}

void Shader::Use()
{
	GraphicsManager::GetGraphicsApi()->SetCurrentShader(shaderId);
}

void Shader::SetBool(string name, bool value)
{
	GraphicsManager::GetGraphicsApi()->SetBoolValueToShader(shaderId, name.c_str(), (int)value);
}

void Shader::SetInt(string name, int value)
{
	GraphicsManager::GetGraphicsApi()->SetIntValueToShader(shaderId, name.c_str(), value);
}

void Shader::SetFloat(string name, float value)
{
	GraphicsManager::GetGraphicsApi()->SetFloatValueToShader(shaderId, name.c_str(), value);
}

void Shader::SetVector4(string name, float value0, float value1, float value2, float value3)
{
	GraphicsManager::GetGraphicsApi()->SetVector4ValueToShader(shaderId, name.c_str(), value0, value1, value2, value3);
}

void Shader::SetMatrix4(string name, const float* value)
{
	GraphicsManager::GetGraphicsApi()->SetMatrix4ValueToShader(shaderId, name.c_str(), value);
}