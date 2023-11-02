#include "GameObject.h"


GameObject::GameObject()
{
	name = "GameObject";
	mParent = nullptr;
	fixed = false;

	mTransform = new COMP_Transform(this);
	mComponents.push_back(mTransform);
}

GameObject::GameObject(GameObject* parent)
{
	name = "GameObject";
	this->mParent = parent;
	fixed = false;

	if (parent != nullptr) {
		parent->mChildren.push_back(this);
	}

	mTransform = new COMP_Transform(this);
	mComponents.push_back(mTransform);
}

GameObject::~GameObject()
{

	name = "";
	mParent = nullptr;

	mTransform = nullptr;

	for (size_t i = 0; i < mComponents.size(); i++)
	{
		delete mComponents[i];
		mComponents[i] = nullptr;
	}
	mComponents.clear();
}

void GameObject::AddComponent(COMP_Type type)
{
	Component* newComponent = new Component(this);

	newComponent->type = type;
	newComponent->active = true;

	mComponents.push_back(newComponent);

	delete newComponent;
}


GameObject* GameObject::GetParent()
{
	return mParent;
}


void GameObject::InspectorWindow()
{
	ImGui::Begin("Inspector");
	ImGui::SameLine;
	ImGui::InputText("Name", string, IM_ARRAYSIZE(string), ImGuiInputTextFlags_EnterReturnsTrue);

	if (ImGui::IsKeyDown(ImGuiKey_Enter))
		name = string;

	for (size_t i = 0; i < mComponents.size(); i++)
	{
		ImGui::NewLine();
		ImGui::Separator();
		ImGui::NewLine();

		mComponents[i]->Inspector();
	}
	ImGui::End();
}