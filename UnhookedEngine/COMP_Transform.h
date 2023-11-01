#pragma once
#include "Globals.h"
#include "Component.h"
#include "GameObject.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "ImGui/imgui.h"


class GameObject;
class Component;


class COMP_Transform : public Component
{
public:

	COMP_Transform();
	COMP_Transform(GameObject* owner);
	~COMP_Transform();

	float4x4 lTransform;

	float3 position, scale, rotation;

	void SetTransformMatrix();

	float4x4 GetTransformMatrix();

}; 
