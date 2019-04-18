#include <unordered_map>
#include "../Common/Graphics/Texture.h"
#pragma once

class TextureManager
{
public:
	static void Init(wstring projectName);
	static void Clean();

	static TextureManager* GetInstance();

	//传入的值不是文件的路径，而是文件在项目文件夹下的相对路径
	Texture* GetTextureByProjectRelativePath(wstring filePath);
private:
	TextureManager() {};
	~TextureManager() {};

	static TextureManager* textureManager;
	unordered_map<wstring, Texture*> textureMap;
	wstring projectName = L"";
};