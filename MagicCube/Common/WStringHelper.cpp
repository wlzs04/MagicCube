#include "WStringHelper.h"

wstring_convert<codecvt_utf8<wchar_t>> WStringHelper::conv;

//StringEnum WStringHelper::GetStringEnum(wstring input)
//{
//	StringEnum tempE = StringEnum::Int;
//	for (int i=0;i<input.size();i++)
//	{
//		if ((input[i]<L'0' || L'9'<input[i]))
//		{
//			if (input[i] == L'.')
//			{
//				if (tempE == StringEnum::Int)
//				{
//					return StringEnum::Float;
//				}
//			}
//			return StringEnum::UnKnown;
//		}
//	}
//	return tempE;
//}

int WStringHelper::GetInt(wstring& value)
{
	return _wtoi(value.c_str());
}

float WStringHelper::GetFloat(wstring& value)
{
	return (float)_wtof(value.c_str());
}

bool WStringHelper::GetBool(wstring& value)
{
	//如果value很长，判断效率会不会比只判断三个false低？还是加上判断吧！
	if (value.size() > 5)
	{
		return false;
	}
	return (value == L"1"
		|| WStringHelper::ToLower(value)== L"true");
}

wstring WStringHelper::ToUpper(wstring value)
{
	for (int i=0;i<value.size();i++)
	{
		value[i] = toupper(value[i]);
	}
	return value;
}

wstring WStringHelper::ToLower(wstring value)
{
	for (int i = 0; i < value.size(); i++)
	{
		value[i] = tolower(value[i]);
	}
	return value;
}

void WStringHelper::Split(wstring ws, wchar_t w,vector<wstring>& v)
{
	size_t pos1 = 0;
	size_t pos2 = ws.find(w);
	while (pos2 >= 0)
	{
		wstring tempws = ws.substr(pos1, (int)(pos2 - pos1));
		if (tempws != L"")
		{
			v.push_back(tempws);
		}
		pos1 = pos2+1;
		pos2= ws.find(w, pos1);
	}
	wstring tempws = ws.substr(pos1);
	if (tempws != L"")
	{
		v.push_back(tempws);
	}
}

wstring WStringHelper::ReplaceAll(wstring originString, wstring beReplaceString, wstring replaceString)
{
	wstring::size_type pos = 0;
	std::string::size_type srclen = beReplaceString.size();
	std::string::size_type dstlen = replaceString.size();

	while ((pos = originString.find(beReplaceString, pos)) != std::wstring::npos)
	{
		originString.replace(pos, srclen, replaceString);
		pos += dstlen;
	}
	return originString;
}

string WStringHelper::WStringToUTF8Buffer(wstring value)
{
	return conv.to_bytes(value);
}

wstring WStringHelper::UTF8BufferToWString(string value)
{
	return conv.from_bytes(value);
}

std::string WStringHelper::WStringToString(wstring value)
{
	return conv.to_bytes(value);
}

std::wstring WStringHelper::StringToWString(string value)
{
	return conv.from_bytes(value);
}

//unordered_map<wstring, int>& StringEnum::GetEnumMap()
//{
//	static unordered_map<wstring, int> anchorEnumMap;
//	if (anchorEnumMap.size() == 0)
//	{
//		anchorEnumMap[L"Int"] = Int;
//		anchorEnumMap[L"Float"] = Float;
//		anchorEnumMap[L"UnKnown"] = UnKnown;
//	}
//	return anchorEnumMap;
//}
