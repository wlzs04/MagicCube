#include "MaterialSlot.h"
#include "../../Manager/GraphicsManager.h"

MaterialSlotBase::MaterialSlotBase(wstring name)
{
	this->name = name;
}

wstring MaterialSlotBase::GetName()
{
	return name;
}

int MaterialSlotBase::GetSlotId()
{
	return slotId;
}

void MaterialSlotBase::SetSlotId(int newSlotId)
{
	slotId = newSlotId;
}

MaterialSlotBool::MaterialSlotBool(wstring name):MaterialSlotBase(name)
{

}

MaterialSlotType MaterialSlotBool::GetMaterialSlotType()
{
	return MaterialSlotType::Bool;
}

void MaterialSlotBool::SetValue(bool newValue)
{
	value = newValue;
}

void MaterialSlotBool::Use()
{
	GraphicsManager::GetGraphicsApi()->SetBoolValueToShaderSlot(GetSlotId(), value);
}

MaterialSlotInt::MaterialSlotInt(wstring name) :MaterialSlotBase(name)
{
}

MaterialSlotType MaterialSlotInt::GetMaterialSlotType()
{
	return MaterialSlotType::Int;
}

void MaterialSlotInt::SetValue(int newValue)
{
	value = newValue;
}

void MaterialSlotInt::Use()
{
	GraphicsManager::GetGraphicsApi()->SetIntValueToShaderSlot(GetSlotId(), value);
}

MaterialSlotFloat::MaterialSlotFloat(wstring name) :MaterialSlotBase(name)
{
}

MaterialSlotType MaterialSlotFloat::GetMaterialSlotType()
{
	return MaterialSlotType::Float;
}

void MaterialSlotFloat::SetValue(float newValue)
{
	value = newValue;
}

void MaterialSlotFloat::Use()
{
	GraphicsManager::GetGraphicsApi()->SetFloatValueToShaderSlot(GetSlotId(), value);
}

MaterialSlotVector4::MaterialSlotVector4(wstring name) :MaterialSlotBase(name)
{
}

MaterialSlotType MaterialSlotVector4::GetMaterialSlotType()
{
	return MaterialSlotType::Vector4;
}

void MaterialSlotVector4::SetValue(float newValue0, float newValue1, float newValue2, float newValue3)
{
	value0 = newValue0;
	value1 = newValue1;
	value2 = newValue2;
	value3 = newValue3;
}

void MaterialSlotVector4::SetValue(glm::vec4 newValue)
{
	value0 = newValue.r;
	value1 = newValue.g;
	value2 = newValue.b;
	value3 = newValue.a;
}

void MaterialSlotVector4::Use()
{
	GraphicsManager::GetGraphicsApi()->SetVector4ValueToShaderSlot(GetSlotId(), value0, value1, value2, value3);
}

MaterialSlotMatrix4::MaterialSlotMatrix4(wstring name) :MaterialSlotBase(name)
{
}

MaterialSlotType MaterialSlotMatrix4::GetMaterialSlotType()
{
	return MaterialSlotType::Matrix4;
}

void MaterialSlotMatrix4::SetValue(float* newValue)
{
	value = newValue;
}

void MaterialSlotMatrix4::Use()
{
	GraphicsManager::GetGraphicsApi()->SetMatrix4ValueToShaderSlot(GetSlotId(), value);
}

MaterialSlotTexture::MaterialSlotTexture(wstring name) :MaterialSlotBase(name)
{
}

MaterialSlotType MaterialSlotTexture::GetMaterialSlotType( )
{
	return MaterialSlotType::Texture;
}

void MaterialSlotTexture::SetValue(int newIndex, int newValue)
{
	index = newIndex;
	value = newValue;
}

void MaterialSlotTexture::Use()
{
	GraphicsManager::GetGraphicsApi()->SetTexture(index, value);
}