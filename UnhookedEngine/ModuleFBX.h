#ifndef MODULEFBX_H
#define MODULEFBX_H
#include "Module.h"
#include "Globals.h"
#include "Light.h"
#include "Application.h"


#include "MathGeoLib/include/Math/float3x3.h"
#include "MathGeoLib/include/Math/float4x4.h"
#include "Primitive.h"

#include "Glew/include/glew.h"

//todo: REMOVE this before 1st delivery!!
#include "glmath.h"
#include <vector>


#define MAX_LIGHTS 8

struct MeshData {
    uint id_index = 0;   // Index buffer ID in VRAM
    uint num_index = 0;  // Number of indices
    uint* index = nullptr;  // Index data

    uint id_vertex = 0;  // Vertex buffer ID in VRAM
    uint num_vertex = 0;  // Number of vertices
    float* vertex = nullptr;  // Vertex data

	//Tex
	uint id_tex = 0;
	//uint textureID = 0;
	uint num_tex = 0;
	float* texCoords = nullptr;
	GLuint textureID;

    void CreateBuffer();
    void CreateBufferTex(const void* checkerImage);
    void DrawFBX();
};

class ModuleFBX : public Module
{
public:
	 ModuleFBX(Application* app, bool start_enabled = true);
	 ~ModuleFBX();

	bool Init() override;
	update_status PreUpdate(float dt);
    update_status Update(float dt) override;
    update_status PostUpdate(float dt) override;
	void LoadFBX(const char* file_path, std::vector<MeshData>& MeshVertex);

	bool CleanUp();


public:

};

#endif // MODULEFBX_H
