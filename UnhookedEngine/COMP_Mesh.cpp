#include "Application.h"
#include "COMP_Mesh.h"
#include "GameObject.h"
#include "ModuleFBX.h"
#include "COMP_Transform.h"


COMP_Mesh::COMP_Mesh() : Component(nullptr)
{
	owner = nullptr;
	mesh = nullptr;
}

COMP_Mesh::COMP_Mesh(GameObject* owner) : Component(owner)
{
	this->owner = owner;
	mesh = nullptr;
}

//COMP_Mesh::COMP_Mesh(GameObject* owner, Mesh_Type _meshType) : Component(owner)
//{
//	type = COMP_Type::MESH;
//	mType = _meshType;
//	this->owner = owner;
//	CreatePrimitive();
//}

COMP_Mesh::~COMP_Mesh()
{
	mesh = nullptr;
}


//void COMP_Mesh::UpdateAABB()
//{
//	for (int i = 0; i < meshes.size(); i++) {
//		if (meshes[i] == nullptr)return;
//
//		meshes[i]->obb = meshes[i]->localAABB;
//		meshes[i]->obb.Transform(owner->mTransform->GetTransformMatrix().Transposed());
//
//		meshes[i]->aabb.SetNegativeInfinity();
//		meshes[i]->aabb.Enclose(meshes[i]->obb);
//	}
//}


//void COMP_Mesh::CreatePrimitive()
//{
//	switch (mType)
//	{
//
//	case(Mesh_Type::FBX):
//		break;
//
//	case(Mesh_Type::CUBE):
//		GO_Primitive = new CubeC();
//		Application::GetApp()->FBX->GO_PrimitiveList.push_back(GO_Primitive);
//		owner->name = "Cube";
//		break;
//
//	case(Mesh_Type::SPHERE):
//		GO_Primitive = new SphereC();
//		Application::GetApp()->FBX->GO_PrimitiveList.push_back(GO_Primitive);
//		owner->name = "Sphere";
//		break;
//
//	case(Mesh_Type::CYLINDER):
//		GO_Primitive = new CylinderC();
//		Application::GetApp()->FBX->GO_PrimitiveList.push_back(GO_Primitive);
//		owner->name = "Cylinder";
//		break;
//
//	case(Mesh_Type::LINE):
//		GO_Primitive = new LineC();
//		Application::GetApp()->FBX->GO_PrimitiveList.push_back(GO_Primitive);
//		owner->name = "Line";
//		break;
//
//	case(Mesh_Type::PLANE):
//		GO_Primitive = new PlaneC();
//		Application::GetApp()->FBX->GO_PrimitiveList.push_back(GO_Primitive);
//		owner->name = "Plane";
//		break;
//
//	default:
//		break;
//	}
//}

void COMP_Mesh::Inspector()
{
	if (ImGui::CollapsingHeader("Mesh"))
	{
		ImGui::LabelText("##%f", "Number of vertex:");
		ImGui::SameLine();
		if (mesh == nullptr) return;
		ImGui::Text("%d", mesh->num_vertex);
	}
}

