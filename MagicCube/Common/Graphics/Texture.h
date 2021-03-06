#pragma once
#include <string>

using namespace std;

class Texture
{
public:
	Texture();
	~Texture();

	void LoadTexture(wstring texturePath);
	unsigned int GetTextureId();
	int GetWidth();
	int GetHeight();
	int GetChannelNumber();
	unsigned char* GetData();
	void ClearData();
private:
	wstring texturePath;
	unsigned int textureId = 0;
	int width = 0;
	int height = 0;
	int channelNumber = 0;
	unsigned char* data = nullptr;
};