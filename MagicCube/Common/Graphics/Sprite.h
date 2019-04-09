#pragma once

class Sprite
{
public:
	Sprite(unsigned int spriteId);

	void Init();
	unsigned int GetSpriteId();
	int GetIndicesNumber();
	void SetIndicesNumber(int indicesNumber);
private:
	unsigned int spriteId = 0;
	int indicesNumber = 0;
};