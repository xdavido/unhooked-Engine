#pragma once

#include "Globals.h"
//#include "Application.h"
#include "ModuleFBX.h"
#include "ModuleTexture.h"
#include "ModuleRenderer3D.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/mesh.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")
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
	//meshData.CalculateVertexNormals();
	
	//Initialize checker image
	/*GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];

	for (int i = 0; i < CHECKERS_HEIGHT; i++) {
		for (int j = 0; j < CHECKERS_WIDTH; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}
	}*/

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
					_MeshVertex.index = new uint[_MeshVertex.num_index]; // each face is a triangle
					for (uint i = 0; i < sceneM->mNumFaces; ++i)
					{
						if (sceneM->mFaces[i].mNumIndices != 3){
							LOG("WARNING, geometry face with != 3 indices!");
						}
						else{
							memcpy(&_MeshVertex.index[i * 3], sceneM->mFaces[i].mIndices, 3 * sizeof(uint));
						}
						
						// copy tex coords
						/*_MeshVertex.texCoords = new float[_MeshVertex.num_vertex * 2];
						for (size_t k = 0; k < sceneM->mNumVertices; k++) {
							if (sceneM->mTextureCoords[0]) {
								_MeshVertex.texCoords[k * 2] = sceneM->mTextureCoords[0][k].x;
								_MeshVertex.texCoords[k * 2 + 1] = sceneM->mTextureCoords[0][k].y;
							}
						}*/

					}
				}

				_MeshVertex.CreateBuffer();
				//_MeshVertex.CreateBufferTex(checkerImage);
		}
		aiReleaseImport(scene);
	}
	else
		LOG("Error loading scene %s", file_path);

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

    for (uint i = 0; i < num_index; i += 3) {
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



void MeshData::DrawFBX()
{
	// Bind vertex and index buffers
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);

	// Enable vertex position and normal attributes (modify according to your data)
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	// Draw the mesh
	glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, 0);

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_COORD_ARRAY);


	
	// Descomentar esto para ver Vertex y Face Normals

	// Draw Face Normals if the flag is set
	/*if (App.editor->FaceShow) {*/
	//for (uint i = 0; i < num_index; i += 3) {
	//	// Calculate the face normal
	//	float normal[3];
	//	CalculateFaceNormal(&vertex[index[i] * 3], &vertex[index[i + 1] * 3], &vertex[index[i + 2] * 3], normal);

	//	// Calculate the center of the face (average of vertices)
	//	float center[3];
	//	center[0] = (vertex[index[i] * 3] + vertex[index[i + 1] * 3] + vertex[index[i + 2] * 3]) / 3;
	//	center[1] = (vertex[index[i] * 3 + 1] + vertex[index[i + 1] * 3 + 1] + vertex[index[i + 2] * 3 + 1]) / 3;
	//	center[2] = (vertex[index[i] * 3 + 2] + vertex[index[i + 1] * 3 + 2] + vertex[index[i + 2] * 3 + 2]) / 3;

	//	// Calculate the end point of the face normal
	//	float endpoint[3];
	//	endpoint[0] = center[0] + normal[0];
	//	endpoint[1] = center[1] + normal[1];
	//	endpoint[2] = center[2] + normal[2];

	//	// Draw the face normal as a line from the center to the end point
	//	glBegin(GL_LINES);
	//	glVertex3fv(center);
	//	glVertex3fv(endpoint);
	//	glEnd();
	//}
	////}
	//// 
	//CalculateVertexNormals();
	////Draw Vertex Normals
	///*if (App.editor->VertexShow) {*/
	//for (uint i = 0; i < num_vertex * 3; i += 3) {
	//	float vertexX = vertex[i];
	//	float vertexY = vertex[i + 1];
	//	float vertexZ = vertex[i + 2];

	//	float normalX = normals[i];
	//	float normalY = normals[i + 1];
	//	float normalZ = normals[i + 2];

	//	// Define a scaling factor for the normal length
	//	float normalScale = 0.1f;

	//	// Calculate the end point of the normal
	//	float normalEndX = vertexX + normalX * normalScale;
	//	float normalEndY = vertexY + normalY * normalScale;
	//	float normalEndZ = vertexZ + normalZ * normalScale;

	//	// Draw the vertex normal as a line
	//	glBegin(GL_LINES);
	//	glVertex3f(vertexX, vertexY, vertexZ);
	//	glVertex3f(normalEndX, normalEndY, normalEndZ);
	//	glEnd();
	//}
	//}
	

}

void MeshData::DrawTexture(GLuint textureID)
{
	//Bind checker texture
	
	glEnable(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Binding buffers
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_index);
	
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * num_tex, texCoords, GL_STATIC_DRAW);


	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	// Tell OpenGL that array vertex is [ x, y, z, u, v ]
	glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTEX_ARGUMENTS, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTEX_ARGUMENTS, (void*)(3 * sizeof(float)));

	// Apply Transform matrix to set Draw offset, then draw 
	glPushMatrix(); // Bind transform matrix


	// Draw
	glDrawElements(GL_TRIANGLES, id_index, GL_UNSIGNED_INT, NULL);

	glPopMatrix(); // Unbind transform matrix

	// Unbind buffers
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_COORD_ARRAY);
}

// Called before quitting
bool ModuleFBX::CleanUp()
{
    LOG("Deleting 3D Render");
	// detach log stream
	aiDetachAllLogStreams();
    return true;

}




