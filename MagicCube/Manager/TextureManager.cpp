#include "TextureManager.h"
#include "../Common/CommonHelper.h"

TextureManager* TextureManager::textureManager = nullptr;

void TextureManager::Init(wstring projectName)
{
	if (textureManager == nullptr)
	{
		textureManager = new TextureManager();
	}
	textureManager->projectName = projectName;
}

void TextureManager::Clean()
{
	if (textureManager != nullptr)
	{
		for (auto var : textureManager->textureMap)
		{
			delete var.second;
		}
		textureManager->projectName = L"";
		delete textureManager;
		textureManager = nullptr;
	}
}

TextureManager* TextureManager::GetInstance()
{
	return textureManager;
}

Texture* TextureManager::GetTextureByProjectRelativePath(wstring filePath)
{
	if (textureMap.count(filePath) > 0)
	{
		return textureMap[filePath];
	}
	else
	{
		Texture* texture = new Texture();
		textureMap[filePath] = texture;
		texture->LoadTexture(CommonHelper::GetCurrentPath() + L"/Project/" + projectName + filePath);
		return texture;
	}
}
