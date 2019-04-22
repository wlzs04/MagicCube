#pragma once
#include "../Common/Graphics/Mesh/MeshBase.h"
#include <vector>

using namespace std;

class MeshManager
{
public:
	static void Init();
	static void Clean();

	static MeshManager* GetInstance();

	//创建立方体
	MeshBase* CreateCube();
	//创建平面
	MeshBase* CreatePlane();
private:
	MeshManager() {};
	~MeshManager() {};

	static MeshManager* meshManager;
	vector<MeshBase*> meshList;
};