#include "../Common/Window/WindowBase.h"
#include <vector>
#include <unordered_map>
#pragma once

//控制台程序不显示控制台黑框 项目属性设置：链接器/系统/子系统/控制台改为窗体
#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")

//窗体管理器
class WindowManager
{
	friend class WindowBase;
public:
	static void Init();
	static void Clean();

	static WindowManager* GetInstance();
	
	//创建窗体
	WindowBase* CreateWindow(int width, int height, wstring title, bool fullSceen = false, bool canResize = true, bool showBorder = true);
private:
	WindowManager() {};
	~WindowManager() {};

	//由WindowBase调用设置回调
	void SetWindowInputKeyCallBack(WindowBase* window, InputKeyHandleEvent inputKeyCallBack);
	void SetWindowInputCharCallBack(WindowBase* window, InputCharHandleEvent inputCharCallBack);
	void SetWindowResizeCallBack(WindowBase* window, ResizeHandleEvent resizeCallBack);
	void SetWindowMouseButtonCallBack(WindowBase* window, ButtonHandleEvent buttonCallBack);
	void SetWindowMousePositionCallBack(WindowBase* window, PositionHandleEvent positionCallBack);
	void SetWindowMouseScrollCallBack(WindowBase* window, ScrollHandleEvent scrollCallBack);

	//静态回调方法
	static void WindowInputKeyCallBack(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
	static void WindowInputCharCallBack(GLFWwindow* glfwWindow, unsigned int charValue);
	static void WindowResizeCallBack(GLFWwindow* glfwWindow, int width, int height);
	static void WindowMouseButtonCallBack(GLFWwindow* glfwWindow, int button, int action, int mods);
	static void WindowMousePositionCallBack(GLFWwindow* glfwWindow, double xPosition,double yPosition);
	static void WindowMouseScrollCallBack(GLFWwindow* glfwWindow, double xoffset, double yoffset);

	static WindowManager* windowManager;
	WindowBase* currentWindow = nullptr;

	vector<WindowBase*> windowList;
	unordered_map<GLFWwindow*, InputKeyHandleEvent> windowInputKeyMap;
	unordered_map<GLFWwindow*, InputCharHandleEvent> windowInputCharMap;
	unordered_map<GLFWwindow*, ResizeHandleEvent> windowResizeMap;
	unordered_map<GLFWwindow*, ButtonHandleEvent> windowButtonMap;
	unordered_map<GLFWwindow*, PositionHandleEvent> windowPositionMap;
	unordered_map<GLFWwindow*, ScrollHandleEvent> windowScrollMap;
};