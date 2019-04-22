#include "MeshManager.h"
#include "GraphicsManager.h"

MeshManager* MeshManager::meshManager = nullptr;

void MeshManager::Init()
{
	if (meshManager == nullptr)
	{
		meshManager = new MeshManager();
	}
}

void MeshManager::Clean()
{
	if (meshManager != nullptr)
	{
		for (auto mesh : meshManager->meshList)
		{
			delete mesh;
		}
		delete meshManager;
		meshManager = nullptr;
	}
}

MeshManager* MeshManager::GetInstance()
{
	return meshManager;
}

MeshBase* MeshManager::CreateCube()
{
	MeshBase* cubeMesh = new MeshBase();

	float width = 1;
	float height = 1;
	float depth = 1;
	float w2 = 0.5f * width;
	float h2 = 0.5f * height;
	float d2 = 0.5f * depth;

	float verticesArray[] =
	{
		-w2, -h2, -d2, 0.0f, 1.0f,
		-w2, +h2, -d2, 0.0f, 0.0f,
		+w2, +h2, -d2, 1.0f, 0.0f,
		+w2, -h2, -d2, 1.0f, 1.0f,

		-w2, -h2, +d2, 1.0f, 1.0f,
		+w2, -h2, +d2, 0.0f, 1.0f,
		+w2, +h2, +d2, 0.0f, 0.0f,
		-w2, +h2, +d2, 1.0f, 0.0f,

		-w2, +h2, -d2, 0.0f, 1.0f,
		-w2, +h2, +d2, 0.0f, 0.0f,
		+w2, +h2, +d2, 1.0f, 0.0f,
		+w2, +h2, -d2, 1.0f, 1.0f,

		-w2, -h2, -d2, 1.0f, 1.0f,
		+w2, -h2, -d2, 0.0f, 1.0f,
		+w2, -h2, +d2, 0.0f, 0.0f,
		-w2, -h2, +d2, 1.0f, 0.0f,

		-w2, -h2, +d2, 0.0f, 1.0f,
		-w2, +h2, +d2, 0.0f, 0.0f,
		-w2, +h2, -d2, 1.0f, 0.0f,
		-w2, -h2, -d2, 1.0f, 1.0f,

		+w2, -h2, -d2, 0.0f, 1.0f,
		+w2, +h2, -d2, 0.0f, 0.0f,
		+w2, +h2, +d2, 1.0f, 0.0f,
		+w2, -h2, +d2, 1.0f, 1.0f,
	};
	vector<float> vertices(verticesArray, verticesArray+24*5);

	unsigned int indicesArray[] =
	{
		0,1,2,
		0,2,3,

		4,5,6,
		4,6,7,

		8,9,10,
		8,10,11,

		12,13,14,
		12,14,15,

		16,17,18,
		16,18,19,

		20,21,22,
		20,22,23,
	};
	vector<unsigned int> indices(indicesArray, indicesArray + 36);

	vector<VertexAttribute> attributes;
	attributes.push_back(VertexAttribute(0, 3));
	attributes.push_back(VertexAttribute(1, 2));

	cubeMesh->SetData(vertices, indices, attributes);
	meshList.push_back(cubeMesh);

	return cubeMesh;
}

MeshBase* MeshManager::CreatePlane()
{
	MeshBase* planeMesh = new MeshBase();

	float width = 1;
	float depth = 1;

	float w2 = 0.5f * width;
	float d2 = 0.5f * depth;

	float verticesArray[] =
	{
		-w2, 0, -d2, 0.0f, 1.0f,
		-w2, 0, +d2, 0.0f, 0.0f,
		+w2, 0, +d2, 1.0f, 0.0f,
		+w2, 0, -d2, 1.0f, 1.0f,
	};
	vector<float> vertices(verticesArray, verticesArray + 24 * 5);
	
	unsigned int indicesArray[] =
	{
		0,1,2,
		0,2,3,
	};
	vector<unsigned int> indices(indicesArray, indicesArray + 36);

	vector<VertexAttribute> attributes;
	attributes.push_back(VertexAttribute(0, 3));
	attributes.push_back(VertexAttribute(1, 2));

	planeMesh->SetData(vertices, indices, attributes);
	meshList.push_back(planeMesh);

	return planeMesh;
}
