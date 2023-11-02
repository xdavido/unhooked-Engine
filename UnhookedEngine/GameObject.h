#pragma once
#include "Globals.h"
#include "ImGui/imgui.h"
#include "Component.h"
#include "COMP_Transform.h"

#include <vector>
#include <string>

enum class COMP_Type;
class Component;
class COMP_Transform;

class GameObject
{
public:
	GameObject();
	~GameObject();

	GameObject(GameObject* parent);

	void InspectorWindow();

	void AddComponent(COMP_Type type);

	GameObject* GetParent();

	std::string name;
	char string[128] = "GameObject";
	GameObject* mParent;
	std::vector<Component*> mComponents;
	std::vector<GameObject*> mChildren;
	bool fixed;
	COMP_Transform* mTransform;

}