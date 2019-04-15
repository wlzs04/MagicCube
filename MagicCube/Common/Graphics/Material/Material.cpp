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

void Material::LoadMaterialFromFile(wstring filePath)
{
	shader = new Shader();
	shader->LoadShader(filePath + L".vs", filePath + L".fs");

	MaterialSlotMatrix4* projectionMatrix4 = new MaterialSlotMatrix4(L"projection");
	MaterialSlotMatrix4* viewMatrix4 = new MaterialSlotMatrix4(L"view");
	MaterialSlotMatrix4* modelMatrix4 = new MaterialSlotMatrix4(L"model");
	MaterialSlotTexture* textureImage = new MaterialSlotTexture(L"textureImage");

	AddSlot(projectionMatrix4);
	AddSlot(viewMatrix4);
	AddSlot(modelMatrix4);
	AddSlot(textureImage);

	LLXMLDocument xml;
	wstring xmlPath = CommonHelper::GetCurrentPath() + L"/Project/MagicCube/Material/Cube.llmat";
	//wstring_convert<codecvt_utf8<wchar_t>> conv;
	//wstring wxmlPath = conv.from_bytes(xmlPath);
	xml.LoadXMLFromFile(xmlPath,FileEncode::UTF_8_NO_BOM);
	LLXMLNode* tempNode = xml.GetRootNode();

}

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
