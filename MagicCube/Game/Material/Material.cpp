#include "Material.h"
#include "MaterialSlot.h"
#include "../../Common/Graphics/Shader.h"
#include "../../Common/XML/XMLHelper.h"
#include "../../Common/CommonHelper.h"
#include "../../Manager/GraphicsManager.h"
#include "../../Manager/TextureManager.h"

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
	LLXMLDocument xml;
	xml.LoadXMLFromFile(filePath, FileEncode::UTF_8_NO_BOM);
	LLXMLNode* rootNode = xml.GetRootNode();

	//设置材质类型
	if (rootNode->GetProperty(L"materialType")->GetValue() == L"Actor")
	{
		shader = new Shader();
		wstring vsPath = CommonHelper::GetCurrentPath() + L"/Project/CommonResource/Shader/Actor.vs";
		wstring psPath = CommonHelper::GetCurrentPath() + L"/Project/CommonResource/Shader/Actor.fs";
		shader->LoadShader(vsPath, psPath);
	}
	else
	{
		//报错
	}

	for(LLXMLNode* childNode : rootNode->GetChildNodeList())
	{
		//添加Shader插槽
		if (childNode->GetName() == L"SlotList")
		{
			for (LLXMLNode* slotNode : childNode->GetChildNodeList())
			{
				wstring slotName = slotNode->GetProperty(L"name")->GetValue();
				wstring typeString = slotNode->GetProperty(L"slotType")->GetValue();
				MaterialSlotBase* materialSolt = nullptr;
				if (typeString == L"Matrix4")
				{
					materialSolt = new MaterialSlotMatrix4(slotName);
				}
				else if(typeString == L"Texture")
				{
					materialSolt = new MaterialSlotTexture(slotName);
					wstring path = slotNode->GetProperty(L"path")->GetValue();
					Texture* texture = TextureManager::GetInstance()->GetTextureByProjectRelativePath(path);
					((MaterialSlotTexture*)materialSolt)->SetValue(0, texture->GetTextureId());
				}
				AddSlot(materialSolt);
			}
		}
	}
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
