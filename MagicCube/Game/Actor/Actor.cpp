#include "Actor.h"
#include "../../ThreeParty/glm/glm.hpp"
#include "../../ThreeParty/glm/ext/matrix_transform.hpp"
#include "../../ThreeParty/glm/gtx/quaternion.hpp"
#include "../../ThreeParty/glm/gtx/transform.hpp"
#include "../../Manager/GraphicsManager.h"
#include "../../Common/Graphics/Mesh/MeshBase.h"
#include "../Material/Material.h"
#include "../Material/MaterialSlot.h"

Actor::Actor(wstring actorName)
{
	this->actorName = actorName;
}

wstring Actor::GetName()
{
	return actorName;
}

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

glm::mat4 Actor::GetWorldMatrix()
{
	return worldMatrix;
}

void Actor::SetPosition(glm::vec3 newPosition)
{
	position = newPosition;
	ResetWorldMatrix();
}

void Actor::SetRotation(glm::vec3 newRotation)
{
	rotationE = newRotation;
	ResetWorldMatrix();
}

void Actor::SetScale(glm::vec3 newScale)
{
	scale = newScale;
	ResetWorldMatrix();
}

void Actor::SetParent(Actor* newParentActor)
{
	if (parentActor != nullptr)
	{
		parentActor->RemoveChild(this);
		parentActor = nullptr;
	}
	parentActor = newParentActor;
}

Actor* Actor::GetParent()
{
	return parentActor;
}

void Actor::AddChild(Actor* childActor)
{
	if (childActor->GetParent() != this)
	{
		childActor->SetParent(this);
		childrenActorList.push_back(childActor);
	}
}

void Actor::RemoveChild(Actor* childActor)
{
	for (int i = 0; i < childrenActorList.size(); i++)
	{
		if (childrenActorList[i] == childActor)
		{
			childrenActorList.erase(childrenActorList.cbegin()+i);
			return;
		}
	}
}

void Actor::ResetWorldMatrix()
{
	worldMatrix = glm::mat4(1.0f);

	worldMatrix = glm::translate(worldMatrix, position);

	glm::quat rotationQ = glm::quat(rotationE);
	glm::mat4 RotationMatrix = glm::toMat4(rotationQ);
	worldMatrix = worldMatrix * RotationMatrix;

	worldMatrix = glm::scale(worldMatrix, scale);

}

void Actor::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	if (material != nullptr)
	{
		MaterialSlotMatrix4* projectionSolt = material->GetMaterialSlot<MaterialSlotMatrix4>(L"projection");
		projectionSolt->SetValue(&projectionMatrix[0][0]);

		MaterialSlotMatrix4* viewSolt = material->GetMaterialSlot<MaterialSlotMatrix4>(L"view");
		viewSolt->SetValue(&viewMatrix[0][0]);

		MaterialSlotMatrix4* modelSolt = material->GetMaterialSlot<MaterialSlotMatrix4>(L"model");
		glm::mat4 meshMatrix = mesh->GetWorldMatrix();
		if (parentActor != nullptr)
		{
			meshMatrix = meshMatrix * parentActor->GetWorldMatrix();
		}
		modelSolt->SetValue(&(meshMatrix[0][0]));

		material->PrepareRender();
	}

	if (mesh != nullptr)
	{
		GraphicsManager::GetGraphicsApi()->DrawSprite(mesh->GetMeshId(), (int)mesh->GetIndices().size());
	}
}
