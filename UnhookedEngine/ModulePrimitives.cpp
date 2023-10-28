//#include "Globals.h"
//#include "ModulePrimitives.h"
//#include "Application.h"
//#include "Module.h"
//#include "ModuleFBX.h"
//
//ModulePrimitives::ModulePrimitives(Application* app, bool start_enabled) : Module(app, start_enabled)
//{
//}
//
//// Destructor
//ModulePrimitives::~ModulePrimitives()
//{
//}
//
//MeshData* ModulePrimitives::CreateCube()
//{
//	float s = 0.5f;
//
//	MeshData* mesh = new Mesh();
//
//	//VERTICES
//	mesh->num_vertices = 8;
//	mesh->vertices = new float[mesh->num_vertices * 3]; 
//
//	for (int i = 0; i < (mesh->num_vertices * 3); i++) {
//		int p = 1;	
//		int count = i / 3;
//		switch (i % 3) {
//			//x
//		case 0:
//			if (count == 0 || count == 3 || count == 4 || count == 7) p = -1;
//			break;
//			//y
//		case 1:
//			if (count == 2 || count == 3 || count == 6 || count == 7) p = -1;
//			break;
//			//z
//		case 2:
//			if (count <= 3) p = -1;
//			break;
//		}
//
//		mesh->vertices[i] = s * p;
//	}
//
//	//INDICES
//	mesh->num_indices = 36;	
//	mesh->indices = new uint[mesh->num_indices];
//
//	uint index[36] =
//	{ 0,3,1,
//	3,2,1,
//	1,2,5,
//	2,6,5,
//	5,6,4,
//	6,7,4,
//	4,7,0,
//	7,3,0,
//	4,0,5,
//	0,1,5,
//	3,7,2,
//	7,6,2 };
//
//	for (int i = 0; i < mesh->num_indices; i++) {
//		mesh->indices[i] = index[i];
//	}
//
//	return mesh;
//}
//
//MeshData* ModulePrimitives::CreateSphere()
//{
//	MeshData* mesh = new Mesh();
//
//
//	return mesh;
//}
//
//MeshData* ModulePrimitives::CreateCylinder()
//{
//	MeshData* mesh = new Mesh();
//
//
//	return mesh;
//}
//
//MeshData* ModulePrimitives::CreatePlane()
//{
//	float s = 0.5;
//
//	MeshData* mesh = new Mesh();
//
//	//VERTICES
//	mesh->num_vertices = 4;
//	mesh->vertices = new float[mesh->num_vertices * 3]; 
//
//	//x y z
//	mesh->vertices[0] = -s;
//	mesh->vertices[1] = 0;
//	mesh->vertices[2] = -s;
//
//	mesh->vertices[3] = s;
//	mesh->vertices[4] = 0;
//	mesh->vertices[5] = -s;
//
//	mesh->vertices[6] = -s;
//	mesh->vertices[7] = 0;
//	mesh->vertices[8] = s;
//
//	mesh->vertices[9] = s;
//	mesh->vertices[10] = 0;
//	mesh->vertices[11] = s;
//
//
//	//INDICES
//	mesh->num_indices = 6;	
//	mesh->indices = new uint[mesh->num_indices];
//
//	mesh->indices[0] = 0;
//	mesh->indices[1] = 2;
//	mesh->indices[2] = 1;
//
//	mesh->indices[3] = 2;
//	mesh->indices[4] = 3;
//	mesh->indices[5] = 1;
//
//
//	return mesh;
//}