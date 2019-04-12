#pragma once
#include "../Shader.h"

class Shader;
class MaterialSlotBase;

class Material
{
public:
	~Material();
	void LoadMaterialFromFile(string filePath);

	void SetSlot(string name, int value);

	Shader* GetShader();
	void PrepareRender();
private:
	Shader* shader;

	vector<MaterialSlotBase*> materialSlotMap;
};