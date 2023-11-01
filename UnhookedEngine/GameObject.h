#pragma once
#include "Globals.h"
#include "ImGui/imgui.h"

#include <vector>
#include <string>
enum class COMP_Type;
class Component;
class COMP_Transform;
class COMP_Mesh;

class GameObject
{
public:
	GameObject();
	~GameObject();
	
	void AddComponent(COMP_Type type);

	GameObject* mParent;
	std::vector<GameObject*> mChildren;
	std::vector<Component*> mComponents;

	COMP_Transform* mTransform;

	std::string name;
	char string[128] = "gameObject";

	void DeleteChild(GameObject* child);
	bool ChangeParent(GameObject* NewParent);
	bool CheckChildOf(GameObject* parent);

	//void DeleteChild(GameObject child);

	GameObject* GetParent();
	COMP_Mesh* GetComponentMesh();
	GameObject* GetCompMesh();

	bool fixed;

	void FixRotationYZ();

	void UpdateRecu();

}