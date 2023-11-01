#pragma once

class GameObject;

enum class COMP_Type
{
	NONE,
	TRANSFORM,
	MESH,
	TEXTURE,
	CAMERA,
};

class Component
{
public:
	Component(GameObject* owner);
	virtual ~Component();

	COMP_Type type;
	bool active;
	GameObject* owner;
};