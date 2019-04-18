#include "Actor.h"
#include "../../Manager/GraphicsManager.h"
#include "../../Common/Graphics/Mesh/MeshBase.h"
#include "../Material/Material.h"
#include "../Material/MaterialSlot.h"

void Actor::SetMesh(MeshBase* newMesh)
{
	mesh = newMesh;
}
MeshBase* Actor::GetMesh()
{
	return mesh;
}

void Actor::SetMaterial(Material* newMaterial)
{
	material = newMaterial;
}

void Actor::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	MaterialSlotMatrix4* projectionSolt = material->GetMaterialSlot<MaterialSlotMatrix4>(L"projection");
	projectionSolt->SetValue(&projectionMatrix[0][0]);

	MaterialSlotMatrix4* viewSolt = material->GetMaterialSlot<MaterialSlotMatrix4>(L"view");
	viewSolt->SetValue(&viewMatrix[0][0]);

	MaterialSlotMatrix4* modelSolt = material->GetMaterialSlot<MaterialSlotMatrix4>(L"model");
	modelSolt->SetValue(&(mesh->GetWorldMatrix()[0][0]));

	material->PrepareRender();

	GraphicsManager::GetGraphicsApi()->DrawSprite(mesh->GetMeshId(), (int)mesh->GetIndices().size());
}
