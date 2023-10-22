#pragma once

#include "Globals.h"
#include "Application.h"
#include "ModuleFBX.h"
#include "Game/Assimp/include/cimport.h"
#include "Game/Assimp/include/scene.h"
#include "Game/Assimp/include/postprocess.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")
#include "ImGui/backends/imgui_impl_sdl2.h"

#define MAX_KEYS 300

struct aiLogStream stream;



ModuleFBX::ModuleFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleFBX::~ModuleFBX()
{
}

// Called before render is available
bool ModuleFBX::Init()
{
	
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

    return true;

}

// Called every draw update
update_status ModuleFBX::PreUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}

void ModuleFBX::LoadFBX(const char* file_path) {
	
	// copy vertices
	ourMesh.num_vertices = aiMesh->mNumVertices;
	ourMesh.vertices = new float[ourMesh.num_vertices * 3];
	memcpy(ourMesh.vertices, aiMesh->mVertices, sizeof(float) * ourMesh.num_vertices * 3);
	LOG("New mesh with %d vertices", m.num_vertices);
	// copy faces
	if (aiMesh->HasFaces())
	{
		ourMesh.num_indices = aiMesh->mNumFaces * 3;
		ourMesh.indices = new uint[m.num_indices]; // assume each face is a triangle
		for (uint i = 0; i < aiMesh->mNumFaces; ++i)
		{
			if (aiMesh->mFaces[i].mNumIndices != 3)
				LOG("WARNING, geometry face with != 3 indices!");
			else
				memcpy(&m.indices[i * 3], new_mesh->mFaces[i].mIndices, 3 * sizeof(uint));
		}
	}
}


// Called before quitting
bool ModuleFBX::CleanUp()
{
    LOG("Deleting 3D Render");
	// detach log stream
	aiDetachAllLogStreams();
    return true;

}




