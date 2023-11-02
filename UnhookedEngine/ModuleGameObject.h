#ifndef MODULEGAMEOBJECT_H
#define MODULEGAMEOBJECT_H
#include "Module.h"
#include "Globals.h"
#include "Light.h"
#include "Application.h"
#include "ModuleTexture.h"


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


#define MAX_LIGHTS 8



class ModuleGameObject : public Module
{
public:
	ModuleGameObject(Application* app, bool start_enabled = true);
	 ~ModuleGameObject();

	bool Init() override;
	update_status PreUpdate(float dt)override;
    update_status Update(float dt) override;
    update_status PostUpdate(float dt) override;
	bool CleanUp();


public:
    
};

#endif // MODULEGAMEOBJECT_H
