#include "Material.h"
#include "MaterialSlot.h"
#include "../Shader.h"
#include "../../XML/XMLHelper.h"
#include "../../CommonHelper.h"
#include "../../../Manager/GraphicsManager.h"

Material::~Material()
{
	for (auto var : materialSlotMap)
	{
		delete var.second;
	}
	
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

	MaterialSlotMatrix4* projectionMatrix4 = new MaterialSlotMatrix4("projection");
	MaterialSlotMatrix4* viewMatrix4 = new MaterialSlotMatrix4("view");
	MaterialSlotMatrix4* modelMatrix4 = new MaterialSlotMatrix4("model");
	MaterialSlotTexture* textureImage = new MaterialSlotTexture("textureImage");

	AddSlot(projectionMatrix4);
	AddSlot(viewMatrix4);
	AddSlot(modelMatrix4);
	AddSlot(textureImage);

	LLXMLDocument xml;
	string xmlPath = CommonHelper::GetCurrentPath() + "/Project/MagicCube/Material/Cube.llmat";
	wstring_convert<codecvt_utf8<wchar_t>> conv;
	wstring wxmlPath = conv.from_bytes(xmlPath);
	xml.LoadXMLFromFile(wxmlPath,FileEncode::UTF_8_NO_BOM);
	LLXMLNode* tempNode = xml.GetRootNode();

}

//MaterialSlotBool* Material::GetSlotBool(string name)
//{
//
//	return nullptr;
//}

//MaterialSlotMatrix4* Material::CreateMatrix4Slot(string name)
//{
//	MaterialSlotMatrix4* materialSlotMatrix4 = new MaterialSlotMatrix4(name);
//	AddSlot(materialSlotMatrix4);
//	return materialSlotMatrix4;
//}

//MaterialSlotBase* Material::GetMaterialSlot(string name)
//{
//	if (materialSlotMap.count(name) > 0)
//	{
//		return materialSlotMap[name];
//	}
//	else
//	{
//		MaterialSlotMatrix4* materialSlotMatrix4 = new MaterialSlotMatrix4(name);
//		int slotId = GraphicsManager::GetGraphicsApi()->GetShaderSlotIdByName(shader->GetShaderId(), materialSlot->GetName());
//		materialSlot->SetSlotId(slotId);
//		materialSlotMap[name] = 
//	}
//	return materialSlotMap[name];
//}

//Shader* Material::GetShader()
//{
//	return shader;
//}

void Material::PrepareRender()
{
	shader->Use();
	for (auto materialSlot : materialSlotMap)
	{
		materialSlot.second->Use();
	}
}

void Material::AddSlot(MaterialSlotBase* materialSlot)
{
	if (materialSlotMap.count(materialSlot->GetName()) > 0)
	{
		//警告
	}
	else
	{
		int slotId = GraphicsManager::GetGraphicsApi()->GetShaderSlotIdByName(shader->GetShaderId(), materialSlot->GetName());
		materialSlot->SetSlotId(slotId);
		materialSlotMap[materialSlot->GetName()] = materialSlot;
	}
}
