#include "RecordBase.h"

void RecorderBase::LoadRecorder(LLXMLNode* xmlNode)
{
	for (auto var : xmlNode->GetPropertyMap())
	{
		valueMap[var.second->GetName()] = var.second->GetValue();
	}

	id = xmlNode->GetProperty(L"id")->GetValueInt();
}

wstring RecorderBase::GetRecordName()
{
	return L"Record";
}

int RecorderBase::GetId()
{
	return id;
}

wstring RecorderBase::GetValueByName(wstring name)
{
	if (valueMap.count(name)>0)
	{
		return valueMap[name];
	}
	return L"";
}
