#include "ProjectBase.h"

ProjectBase::ProjectBase(wstring projectName)
{
	this->projectName = projectName;
	WindowManager::Init();
	GraphicsManager::Init();
	TextureManager::Init(projectName);
	MeshManager::Init();
	SceneManager::Init(projectName);
}

ProjectBase::~ProjectBase()
{
	if (projectTimeHelper != nullptr)
	{
		delete projectTimeHelper;
		projectTimeHelper = nullptr;
	}
	if (projectConfig != nullptr)
	{
		delete projectConfig;
		projectConfig = nullptr;
	}

	SceneManager::Clean();
	MeshManager::Clean();
	TextureManager::Clean();
	GraphicsManager::Clean();
	WindowManager::Clean();
}

void ProjectBase::Init()
{
	LoadProjectConfigBase();

	window = WindowManager::GetInstance()->CreateWindow(projectConfig->GetWidth(), projectConfig->GetHeight(), projectConfig->GetProjectName(), projectConfig->GetFullScreen(), projectConfig->GetCanResize(), projectConfig->GetShowBorder());
	window->BindWindowInputKeyCallBack([this](int key, int action)-> void {InputKeyCallBackBase(key, action); });
	window->BindWindowResizeCallBack([this](int width, int height)-> void {WindowSizeChangeCallBackBase(width, height); });
	window->BindWindowMouseButtonCallBack([this](int key, int action)-> void {MouseButtonCallBackBase(key, action); });
	window->BindWindowMousePositionCallBack([this](double xPosition, double yPosition)-> void {MousePositionCallBackBase(xPosition, yPosition); });
	window->BindRunFunction([this]()-> void {EveryTickCallBackBase(); });

	GraphicsManager::SetGraphicsApiType(GraphicsApiType::OpenGL);
	graphicsApi = GraphicsManager::GetGraphicsApi();
	graphicsApi->SetViewPortSize(projectConfig->GetWidth(), projectConfig->GetHeight());

	Scene* scene = SceneManager::GetInstance()->CreateScene(L"MainScene");
	SceneManager::GetInstance()->SetCurrentScene(scene);

	camera = scene->CreateCamera();
	camera->SetPosition(glm::vec3(0, 0, 5));
	camera->SetDirection(glm::vec3(0, 0, -1));
	camera->SetSpeed(3);
	camera->SetSensitivity(0.3f);
	camera->SetViewSize(projectConfig->GetWidth(), projectConfig->GetHeight());

	projectTimeHelper = new TimeHelper();

	InitProject();
}

void ProjectBase::StartRun()
{
	projectTimeHelper->Start();
	window->Run();
}

void ProjectBase::End()
{
	projectTimeHelper->Reset();
	window->Close();
}

WindowBase* ProjectBase::GetWindow()
{
	return window;
}

GraphicsApi* ProjectBase::GetGraphicsApi()
{
	return graphicsApi;
}

Camera* ProjectBase::GetCamera()
{
	return camera;
}

TimeHelper* ProjectBase::GetProjectTimeHelper()
{
	return projectTimeHelper;
}

wstring ProjectBase::GetProjectPath()
{
	return CommonHelper::GetCurrentPath() + L"/Project/" + projectName;
}

void ProjectBase::InputKeyCallBackBase(int key, int action)
{
	InputKeyCallBack(key, action);
}

void ProjectBase::WindowSizeChangeCallBackBase(int width, int height)
{
	graphicsApi->SetViewPortSize(width, height);
	camera->SetViewSize(width, height);
	WindowSizeChangeCallBack(width, height);
}

void ProjectBase::MouseButtonCallBackBase(int key, int action)
{
	MouseButtonCallBack(key,action);
}

void ProjectBase::MousePositionCallBackBase(double xPosition, double yPosition)
{
	MousePositionCallBack(xPosition, yPosition);
}

void ProjectBase::WindowMouseScrollCallBackBase(double yoffset)
{
	WindowMouseScrollCallBack(yoffset);
}

void ProjectBase::EveryTickCallBackBase()
{
	projectTimeHelper->Tick();
	graphicsApi->ClearViewPort();

	EveryTickCallBack();

	SceneManager::GetInstance()->GetCurrentScene()->RenderSceneToCamera(camera);
}

void ProjectBase::LoadProjectConfigBase()
{
	projectConfig = new ProjectConfig();
	projectConfig->LoadFromLLXMLNode(CommonHelper::GetCurrentPath()+ L"/Project/"+projectName+L"/Config.xml");

	LoadProjectConfig();
}
