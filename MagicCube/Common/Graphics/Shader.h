#pragma once
#include <string>
#include <iostream>
using namespace std;

//着色器类
class Shader
{
public:
	void LoadShader(wstring vertexShaderPath, wstring fragmentShaderPath);
	void Use();
	int GetShaderId();
private:
	unsigned int shaderId = 0;
	wstring vertexShaderPath;
	wstring fragmentShaderPath;
};