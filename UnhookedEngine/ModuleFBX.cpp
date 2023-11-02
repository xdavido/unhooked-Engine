#pragma once

#include "Globals.h"
#include "Application.h"
#include "ModuleFBX.h"
#include "ModuleTexture.h"
#include "ModuleRenderer3D.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")
#include "ImGui/backends/imgui_impl_sdl2.h"
#include "Primitive.h"

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
bool ModuleFBX::Start()
{
	App->editor->AddToConsole("Initializing external libraries...");
	LOG("Creating 3D Renderer context");
	bool ret = true;

	// Stream log messages to Debug window
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	House_Path = "Assets/BakerHouse.fbx";

	LoadFBX(House_Path);

	App->editor->AddToConsole("External libraries initialization complete");

	return ret;
}

// Called every draw update
update_status ModuleFBX::PreUpdate(float dt)
{
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

void ModuleFBX::LoadFBX(string file_path) {
	//meshData.CalculateVertexNormals();
	App->editor->AddToConsole("Loading FBX...");
	
	const aiScene* scene = aiImportFile(file_path.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			MeshData* _MeshVertex =new MeshData();

			// copy vertex
			_MeshVertex->num_vertex = scene->mMeshes[i]->mNumVertices;
			_MeshVertex->vertex = new float[_MeshVertex->num_vertex * VERTEX_ARGUMENTS];

			for (int k = 0; k < _MeshVertex->num_vertex; k++) 
			{
				_MeshVertex->vertex[k * VERTEX_ARGUMENTS] = scene->mMeshes[i]->mVertices[k].x;
				_MeshVertex->vertex[k * VERTEX_ARGUMENTS + 1] = scene->mMeshes[i]->mVertices[k].y;
				_MeshVertex->vertex[k * VERTEX_ARGUMENTS + 2] = scene->mMeshes[i]->mVertices[k].z;

				_MeshVertex->vertex[k * VERTEX_ARGUMENTS + 3] = scene->mMeshes[i]->mTextureCoords[0][k].x;
				_MeshVertex->vertex[k * VERTEX_ARGUMENTS + 4] = 1 - scene->mMeshes[i]->mTextureCoords[0][k].y;
			}
			LOG("New mesh with %d vertices", _MeshVertex->num_vertex);

			// copy faces
				if (scene->mMeshes[i]->HasFaces())
				{
					_MeshVertex->num_index = scene->mMeshes[i]->mNumFaces * 3;
					_MeshVertex->index = new uint[_MeshVertex->num_index]; // each face is a triangle

					for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++)
					{
						if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3){
							LOG("WARNING, geometry face with != 3 indices!");
						}
						else{
							memcpy(&_MeshVertex->index[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
						}
					}
					_MeshVertex->texture_id = App->texture->textureID;
					_MeshVertex->texture_height = App->texture->textureWidth;
					_MeshVertex->texture_width = App->texture->textureWidth;

					CreateBuffer(_MeshVertex);
					//_MeshVertex.CreateBufferTex(checkerImage);
				}
				else {
					delete _MeshVertex;
				}
		}
		aiReleaseImport(scene);
		App->editor->AddToConsole("Fbx load successful");
	}
	else {
		LOG("Error loading scene %s", file_path);
		App->editor->AddToConsole("Error loading Fbx");
	}
}

void ModuleFBX::CreateBuffer(MeshData* Mesh_Vertex)
{
	//vertex
	glEnableClientState(GL_VERTEX_ARRAY);
	glGenBuffers(1, (GLuint*)&(Mesh_Vertex->id_vertex));
	glBindBuffer(GL_ARRAY_BUFFER, Mesh_Vertex->id_vertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Mesh_Vertex->num_vertex * VERTEX_ARGUMENTS, Mesh_Vertex->vertex, GL_STATIC_DRAW);
	// index
	glGenBuffers(1, (GLuint*)&(Mesh_Vertex->id_index));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Mesh_Vertex->id_index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * Mesh_Vertex->num_index, Mesh_Vertex->index, GL_STATIC_DRAW);
	
	glDisableClientState(GL_VERTEX_ARRAY);

	//Add mesh to meshes vector
	MeshVertex.push_back(Mesh_Vertex);
}


void CalculateFaceNormal(const float vertex1[3], const float vertex2[3], const float vertex3[3], float normal[3]) {
	float v1[3], v2[3];

	// Calcula dos vectores que representan los lados del triángulo
	for (int i = 0; i < 3; ++i) {
		v1[i] = vertex2[i] - vertex1[i];
		v2[i] = vertex3[i] - vertex1[i];
	}
	// Calcula la normal de la cara
	normal[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
	normal[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
	normal[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
}

void MeshData::CalculateVertexNormals() {
    if (num_vertex == 0 || num_index == 0) {
        return;
    }
    //Inicializamos todas las normales de los vértices a (0, 0, 0)
	normals = new float[num_vertex * 3]();

    for (uint i = 0; i <num_index; i += 3) {
        uint index1 = index[i] * 3;
        uint index2 = index[i + 1] * 3;
        uint index3 = index[i + 2] * 3;

        //Obtenemos los vértices de la cara
        float vertex1[3] = { vertex[index1], vertex[index1 + 1], vertex[index1 + 2] };
        float vertex2[3] = { vertex[index2], vertex[index2 + 1], vertex[index2 + 2] };
        float vertex3[3] = { vertex[index3], vertex[index3 + 1], vertex[index3 + 2] };

        //Calcula la normal de la cara
        float faceNormal[3];
        CalculateFaceNormal(vertex1, vertex2, vertex3, faceNormal);

        //Agregamos la normal de la cara a las normales de los vértices
        for (int j = 0; j < 3; ++j) {
            normals[index1 + j] += faceNormal[j];
            normals[index2 + j] += faceNormal[j];
            normals[index3 + j] += faceNormal[j];
        }
    }

    //Normalizamos todas las normales de los vértices
    for (uint i = 0; i < num_vertex * 3; i += 3) {
        float normal[3] = { normals[i], normals[i + 1], normals[i + 2] };
        NormalizeVector(normal[0], normal[1], normal[2]);
        normals[i] = normal[0];
        normals[i + 1] = normal[1];
        normals[i + 2] = normal[2];
    }
}

void ModuleFBX::DrawMesh()
{
	for (int i = 0; i < MeshVertex.size(); i++) {
		MeshVertex[i]->DrawFBX();
	}
	if (App->editor->FaceShow) {
		for (int i = 0; i < MeshVertex.size(); i++) {
			MeshVertex[i]->DrawFacesN();
		}
	}
	if (App->editor->VertexShow) {
		for (int i = 0; i < MeshVertex.size(); i++) {
			MeshVertex[i]->DrawVertexN();
		}
	}
}

void MeshData::DrawFBX()
{
	// textures
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	// Bind vertex and index buffers
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_ARGUMENTS, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_ARGUMENTS, (void*)(sizeof(float) * 3));

	// bind texture
	glBindTexture(GL_TEXTURE_2D, texture_id);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	// Draw the mesh
	glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	// Cleaning tex
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_COORD_ARRAY);
}

void MeshData::DrawFacesN() {
	const float normalScale = 1.0f; // Adjust the scaling factor as needed
	const float normalColor[3] = { 1.0f, 0.0f, 0.0f }; // Red color

	for (uint i = 0; i < num_index; i += 3) {
		// Calculate the face normal
		float normal[3];
		CalculateFaceNormal(&vertex[index[i] * VERTEX_ARGUMENTS], &vertex[index[i + 1] * VERTEX_ARGUMENTS], &vertex[index[i + 2] * VERTEX_ARGUMENTS], normal);

		// Calculate the center of the face (average of vertices)
		float center[3];
		center[0] = (vertex[index[i] * VERTEX_ARGUMENTS] + vertex[index[i + 1] * VERTEX_ARGUMENTS] + vertex[index[i + 2] * VERTEX_ARGUMENTS]) / 3;
		center[1] = (vertex[index[i] * VERTEX_ARGUMENTS + 1] + vertex[index[i + 1] * VERTEX_ARGUMENTS + 1] + vertex[index[i + 2] * VERTEX_ARGUMENTS + 1]) / 3;
		center[2] = (vertex[index[i] * VERTEX_ARGUMENTS + 2] + vertex[index[i + 1] * VERTEX_ARGUMENTS + 2] + vertex[index[i + 2] * VERTEX_ARGUMENTS + 2]) / 3;

		// Calculate the end point of the scaled face normal
		float endpoint[3];
		endpoint[0] = center[0] + normal[0] * normalScale;
		endpoint[1] = center[1] + normal[1] * normalScale;
		endpoint[2] = center[2] + normal[2] * normalScale;

		// Set the color for this face normal
		glColor3fv(normalColor);

		// Draw the scaled face normal as a line from the center to the end point
		glBegin(GL_LINES);
		glVertex3fv(center);
		glVertex3fv(endpoint);
		glEnd();
	}
}

void MeshData::DrawVertexN() {

	const float normalScale = 0.5f; // Adjust the scaling factor as needed
	const float normalColor[3] = { 0.0f, 0.0f, 1.0f }; // Blue color

	// Calculate vertex normals before drawing them
	CalculateVertexNormals();

	// Set the color for vertex normals
	glColor3fv(normalColor);

	// Draw Vertex Normals
	for (uint i = 0; i < num_vertex; ++i) {
		// Calculate the end point of the scaled vertex normal
		float endpoint[3];
		endpoint[0] = vertex[i * VERTEX_ARGUMENTS] + normals[i * 3] * normalScale;
		endpoint[1] = vertex[i * VERTEX_ARGUMENTS + 1] + normals[i * 3 + 1] * normalScale;
		endpoint[2] = vertex[i * VERTEX_ARGUMENTS + 2] + normals[i * 3 + 2] * normalScale;

		// Draw the scaled vertex normal as a line from the vertex position to the end point
		glBegin(GL_LINES);
		glVertex3fv(&vertex[i * VERTEX_ARGUMENTS]);
		glVertex3fv(endpoint);
		glEnd();
	}
}
// Called before quitting
bool ModuleFBX::CleanUp()
{
    LOG("Deleting 3D Render");
	//Delete Meshes array
	for (int i = 0; i < MeshVertex.size(); i++) {
		delete MeshVertex[i];
		MeshVertex[i] = nullptr;
	}
	MeshVertex.clear();
	// detach log stream
	aiDetachAllLogStreams();
    return true;
}




