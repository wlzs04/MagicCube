#include "MagicCube.h"
#include "../Manager/WindowManager.h"
#include "../Common/CommonHelper.h"
#include "../Manager/GraphicsManager.h"
#include "../Common/Graphics/GraphicsApi.h"
#include <functional>

MagicCube::MagicCube()
{
	WindowManager::Init();
	GraphicsManager::Init();
}

MagicCube::~MagicCube()
{
	GraphicsManager::Clean();
	WindowManager::Clean();
}

void MagicCube::Init()
{
	window = WindowManager::GetInstance()->CreateWindow(800, 600, "领会");
	window->BindWindowInputCallBack([this](int key, int action)-> void {InputCallBack(key, action); });
	window->BindRunFunction([this]()-> void {RunFunction(); });
	GraphicsManager::SetGraphicsApiType(GraphicsApiType::OpenGL);
	graphicsApi = GraphicsManager::GetGraphicsApi();
	shader = graphicsApi->LoadShader("E:/tomb/c++/OpenGLTest/Project1/Project1/learn4Vectex.glsl", "E:/tomb/c++/OpenGLTest/Project1/Project1/learn4Fragment.glsl");
	texture = graphicsApi->LoadTexture("E:/tomb/c++/OpenGLTest/Project1/Project1/me.jpg");
	sprite = graphicsApi->GetRectangle();
}

void MagicCube::Run()
{
	window->Run();
}

void MagicCube::End()
{
	window->Close();
}

void MagicCube::InputCallBack(int key, int action)
{
	switch (key)
	{
	case 'q':
	case 'Q':
		End();
	default:
		break;
	}
}

void MagicCube::RunFunction()
{
	graphicsApi->ClearViewPort();
	shader->Use();
	//shader->SetFloat("ourColor", 0.5);

	 // 在绑定纹理之前先激活纹理单元
	
	graphicsApi->SetCurrentTexture(texture);
	//shader->SetInt("texture0", 0); // 或者使用着色器类设置

	graphicsApi->DrawSprite(sprite);
}
