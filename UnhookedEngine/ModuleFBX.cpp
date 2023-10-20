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



}

// Called every draw update
update_status ModuleFBX::PreUpdate(float dt)
{
	
	return UPDATE_CONTINUE;
}



// Called before quitting
bool ModuleFBX::CleanUp()
{
	// detach log stream
	aiDetachAllLogStreams();
}

struct MeshData {
    uint id_index = 0;   // Index buffer ID in VRAM
    uint num_index = 0;  // Number of indices
    uint* index = nullptr;  // Index data

    uint id_vertex = 0;  // Vertex buffer ID in VRAM
    uint num_vertex = 0;  // Number of vertices
    float* vertex = nullptr;  // Vertex data

    // Constructor to initialize members
    MeshData() : id_index(0), num_index(0), index(nullptr), id_vertex(0), num_vertex(0), vertex(nullptr) {}

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
void LoadFBX(const char* file_path) {
    const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
    if (scene != nullptr && aiScene > HasMeshes())
    {
        // Use scene->mNumMeshes to iterate on scene->mMeshes array
        aiReleaseImport(scene);
    }
}