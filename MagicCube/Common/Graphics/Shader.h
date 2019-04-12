#pragma once
#include <string>
#include <iostream>

using namespace std;

//着色器类
class Shader
{
public:
	void LoadShader(string vertexShaderPath, string fragmentShaderPath);
	void Use();

	void SetBool(string name, bool value);
	void SetInt(string name, int value);
	void SetFloat(string name, float value);
	void SetVector4(string name, float value0, float value1, float value2, float value3);
	void SetMatrix4(string name, const float* value); //&matrix4[0][0]
private:
	unsigned int shaderId;
	string vertexShaderPath;
	string fragmentShaderPath;
};