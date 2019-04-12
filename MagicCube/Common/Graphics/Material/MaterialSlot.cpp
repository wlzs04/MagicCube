#include "MaterialSlot.h"

void MaterialSlotBase::SetName(string newName)
{
	name = newName;
}

void MaterialSlotInt::SetValue(int newValue)
{
	value = newValue;
}

void MaterialSlotFloat::SetValue(float newValue)
{
	value = newValue;
}

void MaterialSlotVector4::SetValue(float newValue0, float newValue1, float newValue2, float newValue3)
{
	value0 = newValue0;
	value1 = newValue1;
	value2 = newValue2;
	value3 = newValue3;
}

void MaterialSlotBool::SetValue(bool newValue)
{
	value = newValue;
}

void MaterialSlotMaterial4::SetValue(float* newValue)
{
	value = newValue;
}
