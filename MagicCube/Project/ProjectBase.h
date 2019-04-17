#pragma once
#include "../Common/CommonHelper.h"
#include "../Manager/WindowManager.h"
#include "../Manager/GraphicsManager.h"
#include "../Manager/MeshManager.h"
#include "../Common/TimeHelper.h"
#include "../Common/Graphics/Camera.h"
#include "../Common/Graphics/Texture.h"
#include "../Common/Graphics/Material/Material.h"

//项目基类：可以直接运行，其它项目可以继承此类，但只能运行一个项目类
//提供：初始化所有管理类、窗体、一个用于观察的摄像机

//项目文件在UTF-8 without bom格式下，会被Visual Studio认为是ANSI格式，可能出现中文乱码.
//需要强制使用UTF-8的格式进行读取，在项目属性设置：C/C++ -> 命令行, 添加"/source-charset:utf-8 /execution-charset:utf-8"

class ProjectBase
{
public:
	ProjectBase();
	~ProjectBase();

	//初始化
	void Init();
	//运行
	void StartRun();
	//结束
	void End();

protected:
	WindowBase* GetWindow();
	GraphicsApi* GetGraphicsApi();
	Camera* GetCamera();
	TimeHelper& GetTimeHelper();

	//重写以下方法
	//初始化项目
	virtual void InitProject() {};
	//每帧运行
	virtual void EveryTickCallBack() {};

	//事件回调
	virtual void InputKeyCallBack(int key, int action) {};
	virtual void WindowSizeChangeCallBack(int width, int height) {};
	virtual void MouseButtonCallBack(int key, int action) {};
	virtual void MousePositionCallBack(double xPosition, double yPosition) {};
	virtual void WindowMouseScrollCallBack(double yoffset) {};

private:
	void EveryTickCallBackBase();

	void InputKeyCallBackBase(int key, int action);
	void WindowSizeChangeCallBackBase(int width, int height);
	void MouseButtonCallBackBase(int key, int action);
	void MousePositionCallBackBase(double xPosition, double yPosition);
	void WindowMouseScrollCallBackBase(double yoffset);

	WindowBase* window = nullptr;
	GraphicsApi* graphicsApi = nullptr;
	Camera* camera = nullptr;

	TimeHelper timeHelper;
};