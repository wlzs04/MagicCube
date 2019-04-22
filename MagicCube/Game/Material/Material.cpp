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
		wstring defindSlotString;
		wstring defindFinalPositionString;
		wstring definwFinalColorString;
		for (LLXMLNode* childNode : rootNode->GetChildNodeList())
		{
			//添加Shader插槽
			if (childNode->GetName() == L"SlotList")
			{
				for (LLXMLNode* slotNode : childNode->GetChildNodeList())
				{
					wstring slotName = slotNode->GetProperty(L"name")->GetValue();
					wstring typeString = slotNode->GetProperty(L"slotType")->GetValue();
					MaterialSlotBase* materialSolt = nullptr;
					defindSlotString.append(L"uniform ");
					if (typeString == L"Matrix4")
					{
						materialSolt = new MaterialSlotMatrix4(slotName);
						defindSlotString.append(L"mat4 ");
					}
					else if (typeString == L"Vector4")
					{
						materialSolt = new MaterialSlotVector4(slotName);
						defindSlotString.append(L"vec4 ");
					}
					else if (typeString == L"Bool")
					{
						materialSolt = new MaterialSlotBool(slotName);
						defindSlotString.append(L"bool ");
					}
					else if (typeString == L"Texture")
					{
						materialSolt = new MaterialSlotTexture(slotName);
						wstring path = slotNode->GetProperty(L"path")->GetValue();
						Texture* texture = TextureManager::GetInstance()->GetTextureByProjectRelativePath(path);
						((MaterialSlotTexture*)materialSolt)->SetValue(0, texture->GetTextureId());
						defindSlotString.append(L"sampler2D ");
					}
					AddSlot(materialSolt);
					defindSlotString.append(slotName);
					defindSlotString.append(L";\n");
				}
			}
			else if(childNode->GetName() == L"VectexShader")
			{
				defindFinalPositionString = childNode->GetInnerText();
			}
			else if (childNode->GetName() == L"PixelShader")
			{
				definwFinalColorString = childNode->GetInnerText();
			}
		}
		wstring vertexShader = Shader::GetVectexShaderCommonValue();
		vertexShader = WStringHelper::ReplaceAll(vertexShader, L"@DefindSlot", defindSlotString);
		vertexShader = WStringHelper::ReplaceAll(vertexShader, L"@DefindFinalPosition", defindFinalPositionString);
		wstring pixelShader = Shader::GetFragmentShaderCommonValue();
		pixelShader = WStringHelper::ReplaceAll(pixelShader, L"@DefindSlot", defindSlotString);
		pixelShader = WStringHelper::ReplaceAll(pixelShader, L"@DefinwFinalColor", definwFinalColorString);
		shader->LoadShaderFromValue(vertexShader, pixelShader);

		ResetAllSlot();
	}
	else
	{
		//报错
	}
}

void Material::ResetAllSlot()
{
	if (shader->GetShaderId() == 0)
	{
		//警告
		return;
	}
	for (auto var : materialSlotMap)
	{
		int slotId = GraphicsManager::GetGraphicsApi()->GetShaderSlotIdByName(shader->GetShaderId(), var.first);
		var.second->SetSlotId(slotId);
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
		materialSlotMap[materialSlot->GetName()] = materialSlot;
		if (shader->GetShaderId() != 0)
		{
			int slotId = GraphicsManager::GetGraphicsApi()->GetShaderSlotIdByName(shader->GetShaderId(), materialSlot->GetName());
			materialSlot->SetSlotId(slotId);
		}
	}
}
