#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../ThreeParty/stb_image.h"
#include "../../Manager/GraphicsManager.h"

Texture::Texture()
{
}

Texture::~Texture()
{
	ClearData();
}

void Texture::LoadTexture(string texturePath)
{
	data = stbi_load(texturePath.c_str(), &width, &height, &channelNumber, 0);

	textureId = GraphicsManager::GetGraphicsApi()->CreateTextureSlot(width, height, channelNumber, data);
}

unsigned int Texture::GetTextureId()
{
	return textureId;
}

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}

int Texture::GetChannelNumber()
{
	return channelNumber;
}

unsigned char* Texture::GetData()
{
	return data;
}

void Texture::ClearData()
{
	if (data != nullptr)
	{
		stbi_image_free(data);
		data = nullptr;
	}
}
