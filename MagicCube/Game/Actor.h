#pragma once
#include "../ThreeParty/glm/glm.hpp"

class MeshBase;
class Material;

class Actor
{
public:
	void SetMesh(MeshBase* newMesh);
	void SetMaterial(Material* newMaterial);

	void Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
private:
	MeshBase* mesh = nullptr;
	Material* material = nullptr;
};