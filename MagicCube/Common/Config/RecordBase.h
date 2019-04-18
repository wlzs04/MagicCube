#include "../XML/XMLHelper.h"
#pragma once

class RecorderBase
{
public:
	virtual void LoadRecorder(LLXMLNode* xmlNode);

	virtual wstring GetRecordName();

	//获得Id
	int GetId();

	//获得指定名称的值
	wstring GetValueByName(wstring name);
protected:

	int id;
	unordered_map<wstring, wstring> valueMap;
};
