#include "COMP_Transform.h"

COMP_Transform::COMP_Transform() : Component(nullptr)
{

}

COMP_Transform::COMP_Transform(GameObject* owner) : Component(owner)
{
	type = COMP_Type::TRANSFORM;
	this->owner = owner;

	lTransform = float4x4::identity;

	position = float3::zero;
	rotation = float3::zero;
	scale = float3::one;
}

COMP_Transform::~COMP_Transform()
{
}

void COMP_Transform::SetTransformMatrix()
{
	float x = rotation.x * DEGTORAD;
	float y = rotation.y * DEGTORAD;
	float z = rotation.z * DEGTORAD;

	Quat q = Quat::FromEulerXYZ(x, y, z);

	lTransform = float4x4::FromTRS(position, q, scale).Transposed();
}

float4x4 COMP_Transform::GetTransformMatrix()
{
	if (owner->mParent == nullptr) {
		return lTransform;
	}
	else {
		return lTransform * owner->mParent->mTransform->GetTransformMatrix();
	}
}