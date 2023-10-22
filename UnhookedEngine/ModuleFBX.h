#ifndef MODULEFBXA_H
#define MODULEFBXA_H
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

    // Constructor to initialize members
    MeshData() : id_index(0), num_index(0), index(nullptr), id_vertex(0), num_vertex(0), vertex(nullptr) {};

    // Destructor to release allocated memory
    ~MeshData() {
        if (index) {
            delete[] index;
            index = nullptr;
        }

        if (vertex) {
            delete[] vertex;
            vertex = nullptr;
        }
    }
};

class ModuleFBX : public Module
{
public:
	 ModuleFBX(Application* app, bool start_enabled = true);
	 ~ModuleFBX();

	bool Init() override;
	update_status PreUpdate(float dt);
	void LoadFBX(const char* file_path);

	bool CleanUp();


public:

};

#endif // MODULEFBXA_H
