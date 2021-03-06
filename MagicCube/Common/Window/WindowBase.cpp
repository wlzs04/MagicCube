#include "WindowBase.h"
#include "../../ThreeParty/GLFW/glfw3.h"
#include "../../Manager/WindowManager.h"
#include "../WStringHelper.h"

WindowBase::~WindowBase()
{
	if (haveCreate)
	{
		Destroy();
	}
}

void WindowBase::Init(int width, int height, wstring title, bool fullSceen, bool canResize, bool showBorder)
{
	if (haveCreate)
	{
		return;
	}

	glfwInit();

	//强制让窗体支持OpenGL3.3，但OpenGL3.3版本以上的新特性反而不支持。注释后没有出现问题。
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

	//Mac OS X系统需要将下面的代码解除注释
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWmonitor* pMonitor = fullSceen? glfwGetPrimaryMonitor():NULL;
	glfwWindowHint(GLFW_RESIZABLE, canResize);
	glfwWindowHint(GLFW_DECORATED, showBorder);
	string aTitle = WStringHelper::WStringToString(title);
	glfwWindow = glfwCreateWindow(width, height, aTitle.c_str(), pMonitor, NULL);

	if (glfwWindow == NULL)
	{
		glfwTerminate(); 
		return ;
	}
	glfwMakeContextCurrent(glfwWindow);

	//绑定事件
	glfwSetKeyCallback(glfwWindow, WindowManager::WindowInputKeyCallBack);
	glfwSetCharCallback(glfwWindow, WindowManager::WindowInputCharCallBack);
	glfwSetFramebufferSizeCallback(glfwWindow, WindowManager::WindowResizeCallBack);
	glfwSetMouseButtonCallback(glfwWindow, WindowManager::WindowMouseButtonCallBack);
	glfwSetCursorPosCallback(glfwWindow, WindowManager::WindowMousePositionCallBack);
	glfwSetScrollCallback(glfwWindow, WindowManager::WindowMouseScrollCallBack);

	this->width = width;
	this->height = height;
	this->title = title;

	haveCreate = true;
}

void WindowBase::BindWindowInputKeyCallBack(InputKeyHandleEvent inputKeyCallback)
{
	WindowManager::GetInstance()->SetWindowInputKeyCallBack(this, inputKeyCallback);
}

void WindowBase::BindWindowInputCharCallBack(InputCharHandleEvent inputCharCallback)
{
	WindowManager::GetInstance()->SetWindowInputCharCallBack(this, inputCharCallback);
}

void WindowBase::BindWindowResizeCallBack(ResizeHandleEvent sizeChangeCallback)
{
	WindowManager::GetInstance()->SetWindowResizeCallBack(this, sizeChangeCallback);
}

void WindowBase::BindWindowMouseButtonCallBack(ButtonHandleEvent buttonCallback)
{
	WindowManager::GetInstance()->SetWindowMouseButtonCallBack(this, buttonCallback);
}

void WindowBase::BindWindowMousePositionCallBack(PositionHandleEvent positionCallback)
{
	WindowManager::GetInstance()->SetWindowMousePositionCallBack(this, positionCallback);
}

void WindowBase::BindWindowMouseScrollCallBack(ScrollHandleEvent scrollCallback)
{
	WindowManager::GetInstance()->SetWindowMouseScrollCallBack(this, scrollCallback);
}

void WindowBase::BindRunFunction(HandleEvent runFunction)
{
	this->runFunction = runFunction;
}

bool WindowBase::CheckInputKeyPressed(int key)
{
	return glfwGetKey(glfwWindow, key) == GLFW_PRESS;
}

void WindowBase::Run()
{
	while (glfwWindow!=nullptr && !glfwWindowShouldClose(glfwWindow))
	{
		if(runFunction!=nullptr)
		{
			runFunction();
		}

		glfwSwapBuffers(glfwWindow);
		glfwPollEvents();
	}
	Destroy();
}

void WindowBase::Close()
{
	glfwSetWindowShouldClose(glfwWindow, true);
}

void WindowBase::Destroy()
{
	if (haveCreate)
	{
		glfwTerminate();
		glfwWindow = nullptr;
		haveCreate = false;
	}
}

GLFWwindow* WindowBase::GetGLFWwindow()
{
	return glfwWindow;
}
