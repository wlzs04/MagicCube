#include "ProjectConfig.h"
#include "../../Common/XML/XMLHelper.h"

void ProjectConfig::LoadFromLLXMLNode(wstring filePath)
{
	LLXMLDocument xml;
	xml.LoadXMLFromFile(filePath, FileEncode::UTF_8_NO_BOM);
	LLXMLNode* rootNode = xml.GetRootNode();

	for (auto var : rootNode->GetPropertyMap())
	{
		if (var.second->GetName() == L"projectName")
		{
			projectName = var.second->GetValue();
		}
		else if(var.second->GetName() == L"fullScreen")
		{
			fullScreen = var.second->GetValueBool();
		}
		else if (var.second->GetName() == L"width")
		{
			width = var.second->GetValueInt();
		}
		else if (var.second->GetName() == L"height")
		{
			height = var.second->GetValueInt();
		}
		else if (var.second->GetName() == L"canResize")
		{
			canResize = var.second->GetValueBool();
		}
		else if (var.second->GetName() == L"showBorder")
		{
			showBorder = var.second->GetValueBool();
		}
	}
}

wstring ProjectConfig::GetProjectName()
{
	return projectName;
}

bool ProjectConfig::GetFullScreen()
{
	return fullScreen;
}

int ProjectConfig::GetWidth()
{
	return width;
}

int ProjectConfig::GetHeight()
{
	return height;
}

bool ProjectConfig::GetCanResize()
{
	return canResize;
}

bool ProjectConfig::GetShowBorder()
{
	return showBorder;
}
