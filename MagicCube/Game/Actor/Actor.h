#pragma once
#include <string>
#include <vector>
#include "../../ThreeParty/glm/glm.hpp"

using namespace std;

class MeshBase;
class Material;

class Actor
{
public:
	Actor(wstring actorName);
	wstring GetName();

	void SetMesh(MeshBase* newMesh);
	MeshBase* GetMesh();
	void SetMaterial(Material* newMaterial);

	void SetPosition(glm::vec3 newPosition);
	void SetRotation(glm::vec3 newRotation);
	void SetScale(glm::vec3 newScale);

	void SetParent(Actor* newParentActor);
	Actor* GetParent();
	void AddChild(Actor* childActor);
	void RemoveChild(Actor* childActor);

	glm::mat4 GetWorldMatrix();

	virtual void Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
private:
	void ResetWorldMatrix();

	MeshBase* mesh = nullptr;
	Material* material = nullptr;
	wstring actorName = L"";

	Actor* parentActor = nullptr;
	vector<Actor*> childrenActorList;
	
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 rotationE = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1, 1, 1);

	glm::mat4 worldMatrix = glm::mat4(1);
};