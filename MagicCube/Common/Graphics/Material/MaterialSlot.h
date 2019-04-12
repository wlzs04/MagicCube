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
};

//材质插槽，用于向shader传递参数
class MaterialSlotBase
{
	friend class Material;
public:
	void SetName(string newName);
private:
	virtual void Use() = 0;
	MaterialSlotType materialSlotType;
	string name;
};

class MaterialSlotBool : public MaterialSlotBase
{
public:
	void SetValue(bool newValue);
private:
	bool value;
};

class MaterialSlotInt : public MaterialSlotBase
{
public:
	void SetValue(int newValue);
private:
	int value;
};

class MaterialSlotFloat : public MaterialSlotBase
{
public:
	void SetValue(float newValue);
private:
	float value;
};

class MaterialSlotVector4 : public MaterialSlotBase
{
public:
	void SetValue(float newValue0, float newValue1, float newValue2, float newValue3);
private:
	float value0;
	float value1;
	float value2;
	float value3;
};

class MaterialSlotMaterial4 : public MaterialSlotBase
{
public:
	void SetValue(float* newValue);
private:
	float* value;
};