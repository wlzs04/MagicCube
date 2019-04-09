#include "Sprite.h"

Sprite::Sprite(unsigned int spriteId)
{
	this->spriteId = spriteId;
}

void Sprite::Init()
{
	
}

unsigned int Sprite::GetSpriteId()
{
	return spriteId;
}

int Sprite::GetIndicesNumber()
{
	return indicesNumber;
}

void Sprite::SetIndicesNumber(int indicesNumber)
{
	this->indicesNumber = indicesNumber;
}
