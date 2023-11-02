#include "COMP_Transform.h"

COMP_Transform::COMP_Transform() : Component(nullptr)
{

}

COMP_Transform::COMP_Transform(GameObject* owner) : Component(owner)
{
	this->owner = owner;


	position = float3::zero;
	rotation = float3::zero;
	scale = float3::one;
}

COMP_Transform::~COMP_Transform()
{
}

void COMP_Transform::SetTransformMatrix(float3 _position, float3 _rotation, float3 _scale)
{
	float x = _rotation.x * DEGTORAD;
	float y = _rotation.y * DEGTORAD;
	float z = _rotation.z * DEGTORAD;

	Quat q = Quat::FromEulerXYZ(x, y, z);

	lTransform = float4x4::FromTRS(_position, q, _scale).Transposed();
}

//float4x4 COMP_Transform::GetTransformMatrix()
//{
//	if (owner->mParent == nullptr) {
//		return lTransform;
//	}
//	else {
//		return lTransform * owner->mParent->mTransform->GetTransformMatrix();
//	}
//}

void COMP_Transform::Inspector()
{

	SetTransformMatrix(position, rotation, scale);

	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Position", &position);

		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Rotation", &rotation);

		ImGui::Text("X\t\t Y\t\t Z");
		ImGui::InputFloat3("Scale", &scale);
	}

}