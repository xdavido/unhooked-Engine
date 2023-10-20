#include <string>

#include "Module.h"
#include "Globals.h"
#include "Light.h"

#include "MathGeoLib/include/Math/float3x3.h"
#include "MathGeoLib/include/Math/float4x4.h"
#include "Primitive.h"

#include "Glew/include/glew.h"

//todo: REMOVE this before 1st delivery!!
#include "glmath.h"


#define MAX_LIGHTS 8

class ModuleFBX : public Module
{
public:
	ModuleFBX(Application* app, bool start_enabled = true);
	~ModuleFBX();

	bool Init();
	update_status PreUpdate(float dt);
	void LoadFBX(const char* file_path);
	
	bool CleanUp();


public:



};