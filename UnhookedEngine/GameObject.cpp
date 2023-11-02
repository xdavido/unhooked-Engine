#include "GameObject.h"
#include "Component.h"
#include "COMP_Transform.h"
#include "COMP_Mesh.h"


GameObject::GameObject()
{
	name = "Game_Object";
	mParent = nullptr;
	fixed = false;

	mTransform = new COMP_Transform(this);
	mComponents.push_back(mTransform);
}

GameObject::GameObject(GameObject* parent)
{
	name = "Game_Object";
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

//void GameObject::DeleteChild(GameObject* child)
//{
//	for (int i = 0; i < mChildren.size(); i++) {
//		if (mChildren[i] == child) {
//			mChildren.erase(mChildren.begin() + i);
//			child->mParent = nullptr;
//		}
//	}
//}
//
//bool GameObject::ChangeParent(GameObject* NewParent)
//{
//	if (mParent != nullptr) {
//		if (NewParent->CheckChildOf(this)) return false;
//
//		mParent->DeleteChild(this);
//	}
//
//	mParent = NewParent;
//	NewParent->mChildren.push_back(this);
//
//	return true;
//}
//
//bool GameObject::CheckChildOf(GameObject* parent)
//{
//	if (parent->mChildren.empty()) return false;
//
//	for (int i = 0; i < parent->mChildren.size(); i++) {
//
//		if (mChildren[i] == this) return true;
//
//	}
//	return false;
//}

GameObject* GameObject::GetParent()
{
	return mParent;
}

//COMP_Mesh* GameObject::GetComponentMesh()
//{
//	for (int i = 0; i < mComponents.size(); i++) {
//
//		if (mComponents[i]->type == COMP_Type::MESH)
//		{
//			return (COMP_Mesh*)mComponents[i];
//		}
//	}
//
//	return nullptr;
//}
//
//GameObject* GameObject::GetCompMesh()
//{
//	for (int i = 0; i < mComponents.size(); i++) {
//
//		if (mComponents[i]->type == COMP_Type::MESH)
//		{
//			return (GameObject*)mComponents[i];
//		}
//	}
//
//	return nullptr;
//}


//void GameObject::FixRotationYZ() {
//
//	mTransform->rotation = float3(mTransform->rotation.x, mTransform->rotation.z, mTransform->rotation.y);
//	mTransform->SetTransformMatrix(position,rotation,_scale);
//	for (int i = 0; i < mChildren.size(); i++) {
//		mChildren[i]->FixRotationYZ();
//	}
//}

//void GameObject::UpdateRecu()
//{
//	if (GetComponentMesh() != nullptr)
//		GetComponentMesh()->UpdateAABB();
//	for (int i = 0; i < mChildren.size(); i++) {
//		mChildren[i]->UpdateRecu();
//	}
//
//}

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