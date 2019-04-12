#include "Material.h"
#include "MaterialSlot.h"
#include "../../../Manager/GraphicsManager.h"

Material::~Material()
{
	if (shader != nullptr)
	{
		delete shader;
		shader = nullptr;
	}
}

void Material::LoadMaterialFromFile(string filePath)
{
	shader = new Shader();
	shader->LoadShader(filePath + ".vs", filePath + ".fs");
}

void Material::SetSlot(string name, int value)
{
	materialSlotMap[name] = value;
}

Shader* Material::GetShader()
{
	return shader;
}

void Material::PrepareRender()
{
	shader->Use();
	for (auto materialSlot : materialSlotMap)
	{
		materialSlot.Use();
	}
}
