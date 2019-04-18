#include <string>
#pragma once

using namespace std;

//材质插槽类型
enum class MaterialSlotType
{
	Bool,
	Int,
	Float,
	Vector4,
	Matrix4,
	Texture,
};

//材质插槽，用于向shader传递参数
class MaterialSlotBase
{
	friend class Material;
public:
	MaterialSlotBase(wstring name);
	wstring GetName();
	virtual MaterialSlotType GetMaterialSlotType() = 0;
protected:
	int GetSlotId();
private:
	void SetSlotId(int newSlotId);
	virtual void Use() = 0;
	wstring name;
	int slotId = 0;
};

class MaterialSlotBool : public MaterialSlotBase
{
public:
	MaterialSlotBool(wstring name);
	MaterialSlotType GetMaterialSlotType() override;
	void SetValue(bool newValue); 
protected:
	void Use() override;
private:
	bool value = false;
};

class MaterialSlotInt : public MaterialSlotBase
{
public:
	MaterialSlotInt(wstring name);
	MaterialSlotType GetMaterialSlotType() override;
	void SetValue(int newValue);
protected:
	void Use() override;
private:
	int value = 0;
};

class MaterialSlotFloat : public MaterialSlotBase
{
public:
	MaterialSlotFloat(wstring name);
	MaterialSlotType GetMaterialSlotType() override;
	void SetValue(float newValue);
protected:
	void Use() override;
private:
	float value = 0;
};

class MaterialSlotVector4 : public MaterialSlotBase
{
public:
	MaterialSlotVector4(wstring name);
	MaterialSlotType GetMaterialSlotType() override;
	void SetValue(float newValue0, float newValue1, float newValue2, float newValue3);
protected:
	void Use() override;
private:
	float value0 = 0;
	float value1 = 0;
	float value2 = 0;
	float value3 = 0;
};

class MaterialSlotMatrix4 : public MaterialSlotBase
{
public:
	MaterialSlotMatrix4(wstring name);
	MaterialSlotType GetMaterialSlotType() override;
	void SetValue(float* newValue);
protected:
	void Use() override;
private:
	float* value = nullptr;
};

class MaterialSlotTexture : public MaterialSlotBase
{
public:
	MaterialSlotTexture(wstring name);
	MaterialSlotType GetMaterialSlotType() override;
	void SetValue(int newIndex,int newValue);
protected:
	void Use() override;
private:
	int index = 0;
	int value = 0;
};