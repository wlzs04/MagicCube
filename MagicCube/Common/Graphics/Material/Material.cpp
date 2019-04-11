#include "Material.h"
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
	shader = GraphicsManager::GetGraphicsApi()->LoadShader(filePath+".vs", filePath + ".fs");
}

Shader* Material::GetShader()
{
	return shader;
}

void Material::PrepareRender()
{
	shader->Use();
}
