#pragma once
#include <unordered_map>

using namespace std;

class Shader;
class MaterialSlotBase;

class Material
{
public:
	~Material();
	void LoadMaterialFromFile(wstring filePath);

	template<class T>
	T* GetMaterialSlot(wstring name)
	{
		return (T*)materialSlotMap[name];
	}

	void PrepareRender();
private:
	void AddSlot(MaterialSlotBase* materialSlot);

	Shader* shader = nullptr;
	unordered_map<wstring,MaterialSlotBase*> materialSlotMap;
};