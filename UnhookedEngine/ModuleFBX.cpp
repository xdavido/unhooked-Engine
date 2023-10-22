#pragma once

#include "Globals.h"
#include "Application.h"
#include "ModuleFBX.h"
#include "Game/Assimp/include/cimport.h"
#include "Game/Assimp/include/scene.h"
#include "Game/Assimp/include/mesh.h"
#include "Game/Assimp/include/postprocess.h"
#pragma comment (lib, "Game/Assimp/libx86/assimp.lib")
#include "ImGui/backends/imgui_impl_sdl2.h"

#define MAX_KEYS 300

#include <vector>
#include <cmath>



#define CHECKERS_HEIGHT 256/4
#define CHECKERS_WIDTH  256/4


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
	LOG("Creating 3D Renderer context");
	bool ret = true;


	return ret;
	

}

// Called every draw update
update_status ModuleFBX::PreUpdate(float dt)
{
	
	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	return UPDATE_CONTINUE;
}

update_status ModuleFBX::Update(float dt)
{


	return UPDATE_CONTINUE;

}


// PostUpdate present buffer to screen
update_status ModuleFBX::PostUpdate(float dt)
{

	return UPDATE_CONTINUE;
}
void ModuleFBX::LoadFBX(const char* file_path, std::vector<MeshData>& MeshVertex) {
	
	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}
	}

	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		MeshVertex.resize(scene->mNumMeshes);

		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
			MeshData& _MeshVertex = MeshVertex[i];
			aiMesh* sceneM = scene->mMeshes[i];

	// copy vertex
	_MeshVertex.num_vertex = sceneM->mNumVertices;
	_MeshVertex.vertex = new float[_MeshVertex.num_vertex * 3];
	memcpy(_MeshVertex.vertex, sceneM->mVertices, sizeof(float) * _MeshVertex.num_vertex * 3);

	LOG("New mesh with %d vertices", _MeshVertex.num_vertex);

	// copy faces
	if (sceneM->HasFaces())
	{
		_MeshVertex.num_index = sceneM->mNumFaces * 3;
		_MeshVertex.index = new uint[_MeshVertex.num_index]; // assume each face is a triangle
		for (uint i = 0; i < sceneM->mNumFaces; ++i)
		{
			if (sceneM->mFaces[i].mNumIndices != 3){
				LOG("WARNING, geometry face with != 3 indices!");
			}
			else{
				memcpy(&_MeshVertex.index[i * 3], sceneM->mFaces[i].mIndices, 3 * sizeof(uint));
			}
		}
	};

	_MeshVertex.CreateBuffer();
	_MeshVertex.CreateBufferTex(checkerImage);
		}
		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene %s", "Assets/warrior.fbx");

}

void MeshData::CreateBuffer()
{
	glGenBuffers(1, &id_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertex * 3, vertex, GL_STATIC_DRAW);

	glGenBuffers(1, &id_index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_index, index, GL_STATIC_DRAW);
}

void MeshData::CreateBufferTex(const void* checkerImage)
{

	//glGenBuffers(1, &textureID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textureID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_tex, texCoords, GL_STATIC_DRAW);
	//abans
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_tex, tex, GL_STATIC_DRAW);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//ara
	/*glGenTextures(1, &id_tex);
	glBindTexture(GL_TEXTURE_2D, id_tex);*/
	//abans

	/*glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);*/

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);

	//glEnable(GL_TEXTURE_2D);
}

void MeshData::DrawFBX()
{
	/*glPushMatrix();
	glMultMatrixf(my_global_transformation_matrix);*/

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	//-- Buffers--//
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	//glBindBuffer(GL_ARRAY_BUFFER, id_tex);
	//abans
	glBindBuffer(GL_ARRAY_BUFFER, textureID);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	//glBindTexture(GL_TEXTURE_2D, id_tex);
	//abans
	glBindTexture(GL_TEXTURE_2D, textureID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);

	//-- Draw --//
	glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);

	//-- UnBind Buffers--//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_TEXTURE_COORD_ARRAY, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//--Disables States--//
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//glPopMatrix();
}

// Called before quitting
bool ModuleFBX::CleanUp()
{
    LOG("Deleting 3D Render");
	// detach log stream
	aiDetachAllLogStreams();
    return true;

}




