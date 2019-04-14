#pragma once
#include <unordered_map>

using namespace std;

class Shader;
class MaterialSlotBase;

class Material
{
public:
	~Material();
	void LoadMaterialFromFile(string filePath);

	template<class T>
	T* GetMaterialSlot(string name)
	{
		return (T*)materialSlotMap[name];
	}

	void PrepareRender();
private:
	void AddSlot(MaterialSlotBase* materialSlot);

	Shader* shader = nullptr;

	unordered_map<string,MaterialSlotBase*> materialSlotMap;
};