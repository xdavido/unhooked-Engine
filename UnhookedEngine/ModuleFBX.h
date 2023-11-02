#ifndef MODULEFBX_H
#define MODULEFBX_H
#include "Module.h"
#include "Globals.h"
#include "Light.h"
#include "Application.h"
#include "ModuleTexture.h"
#include "ModuleRenderer3D.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/mesh.h"
#include "Assimp/include/postprocess.h"

#include "MathGeoLib/include/Math/float3x3.h"
#include "MathGeoLib/include/Math/float4x4.h"
#include "Primitive.h"

#include "Glew/include/glew.h"
#include "DevIL/include/il.h"
#include "DevIL/include/ilu.h"
#include "DevIL/include/ilut.h"

//todo: REMOVE this before 1st delivery!!
#include "glmath.h"
#include <vector>
using namespace std;

#define VERTEX_ARGUMENTS 5

#define MAX_LIGHTS 8

struct MeshData {
    uint id_index = 0;   // Index buffer ID in VRAM
    uint num_index = 0;  // Number of indices
    uint* index = nullptr;  // Index data

    uint id_vertex = 0;  // Vertex buffer ID in VRAM
    uint num_vertex = 0;  // Number of vertices
    float* vertex = nullptr;  // Vertex data
    
    GLuint texture_id = 0, texture_width = 0, texture_height = 0;;
	
    //Draw Mesh
    void DrawFBX();
    // Normals
    void CalculateVertexNormals();
    uint num_normals = 0;
    float* normals = nullptr;
    void NormalizeNormals() {
        for (uint i = 0; i < num_normals; i += 3) {
            float x = normals[i];
            float y = normals[i + 1];
            float z = normals[i + 2];
            NormalizeVector(x, y, z);
            normals[i] = x;
            normals[i + 1] = y;
            normals[i + 2] = z;
        }
    }
    void NormalizeVector(float& x, float& y, float& z) {
        float length = sqrt(x * x + y * y + z * z);
        if (length != 0.0f) {
            x /= length;
            y /= length;
            z /= length;
        }
    }
    bool drawVertexNormals = true;
    bool drawFaceNormals = true;

    //DRAW VERTEX AND FACES
    void DrawFacesN();
    void DrawVertexN();

private:
    
};

class ModuleFBX : public Module
{
public:
	 ModuleFBX(Application* app, bool start_enabled = true);
	 ~ModuleFBX();

	bool Start() override;
	update_status PreUpdate(float dt)override;
    update_status Update(float dt) override;
    update_status PostUpdate(float dt) override;
	void LoadFBX(string file_path);
    void CreateBuffer(MeshData* Mesh_Vertex);
	bool CleanUp();
    void DrawMesh();

    vector<MeshData*> MeshVertex;
    string House_Path = "";
};

#endif // MODULEFBX_H
