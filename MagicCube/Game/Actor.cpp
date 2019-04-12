#include "Actor.h"
#include "../Manager/GraphicsManager.h"
#include "../Common/Graphics/Mesh/MeshBase.h"
#include "../Common/Graphics/Material/Material.h"

void Actor::SetMesh(MeshBase* newMesh)
{
	mesh = newMesh;
}

void Actor::SetMaterial(Material* newMaterial)
{
	material = newMaterial;
}

void Actor::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	material->PrepareRender();

	material->GetShader()->SetMatrix4("projection", &projectionMatrix[0][0]);
	material->GetShader()->SetMatrix4("view", &viewMatrix[0][0]);
	material->GetShader()->SetMatrix4("model", &(mesh->GetWorldMatrix()[0][0]));

	GraphicsManager::GetGraphicsApi()->DrawSprite(mesh->GetMeshId(), (int)mesh->GetIndices().size());
}
