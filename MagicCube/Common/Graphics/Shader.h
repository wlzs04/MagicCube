#pragma once
#include <string>
#include <iostream>
using namespace std;



//着色器类
class Shader
{
public:
	void LoadShaderFromPath(wstring vertexShaderPath, wstring fragmentShaderPath);
	void LoadShaderFromValue(wstring vertexShader, wstring fragmentShader);
	void Use();
	int GetShaderId();

	static wstring GetVectexShaderCommonValue();
	static wstring GetFragmentShaderCommonValue();
private:
	unsigned int shaderId = 0;
	wstring vertexShaderPath;
	wstring fragmentShaderPath;
};