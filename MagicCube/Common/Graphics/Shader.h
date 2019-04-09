#pragma once
#include <string>
#include <iostream>

using namespace std;

class Shader
{
public:
	Shader(string vertexShaderPath, string fragmentShaderPath);

	void Use();

	void SetBool(string name, bool value);
	void SetInt(string name, int value);
	void SetFloat(string name, float value);
	void SetVector4(string name, float value0, float value1, float value2, float value3);
private:
	static unsigned int LoadShader(string shaderPath, unsigned int shaderType);

	unsigned int shaderProgramId;
	string vertexShaderPath;
	string fragmentShaderPath;
};