#include "WindowBase.h"
#include "../../ThreeParty/GLFW/glfw3.h"
#include "../../Manager/WindowManager.h"

WindowBase::~WindowBase()
{
	if (haveCreate)
	{
		Destroy();
	}
}

void WindowBase::Init(int width, int height, string title)
{
	if (haveCreate)
	{
		return;
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Mac OS X系统需要将下面的代码解除注释
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (glfwWindow == NULL)
	{
		glfwTerminate();
		return ;
	}
	glfwMakeContextCurrent(glfwWindow);

	//绑定事件
	//窗体输入回调
	glfwSetKeyCallback(glfwWindow, WindowManager::WindowInputCallBack);
	//窗体大小改变回调
	glfwSetFramebufferSizeCallback(glfwWindow, WindowManager::WindowResizeCallBack);

	this->width = width;
	this->height = height;
	this->title = title;

	haveCreate = true;
}

void WindowBase::BindWindowResizeCallBack(ResizeHandleEvent sizeChangeCallback)
{
	WindowManager::GetInstance()->SetWindowResizeCallBack(this, inputCallback);
}

void WindowBase::BindWindowInputCallBack(InputHandleEvent inputCallback)
{
	WindowManager::GetInstance()->SetWindowInputCallBack(this, inputCallback);
}

void WindowBase::BindRunFunction(HandleEvent runFunction)
{
	this->runFunction = runFunction;
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
