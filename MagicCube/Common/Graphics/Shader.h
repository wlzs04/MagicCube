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
	int GetShaderId();
private:
	unsigned int shaderId = 0;
	string vertexShaderPath;
	string fragmentShaderPath;
};