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

	//创建网格物体
	MeshBase* CreateCube();
private:
	MeshManager() {};
	~MeshManager() {};

	static MeshManager* meshManager;
	vector<MeshBase*> meshList;
};