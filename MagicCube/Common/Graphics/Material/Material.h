#pragma once
#include "../Shader.h"

class Material
{
public:
	~Material();
	void LoadMaterialFromFile(string filePath);

	Shader* GetShader();
	void PrepareRender();
private:
	Shader* shader;
};