#include "Application.h"


Application* Application::externalapp = nullptr;

Application::Application()
{
	externalapp = this;

	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	editor = new ModuleEditor(this);
	FBX = new ModuleFBX(this);
	texture = new ModuleTexture(this);
	hierarchy = new ModuleHierarchy(this);
	scene = new ModuleScene(this);

	LOG("...");

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);


	AddModule(texture);
	AddModule(FBX);
	AddModule(hierarchy);
	AddModule(scene);
	AddModule(editor);
	// Renderer last!
	AddModule(renderer3D);
	
}

Application* Application::GetApp()
{
	if (externalapp == nullptr)
	{
		externalapp = new Application();
	}
	return externalapp;
}

Application::~Application()
{
	for (int i = list_modules.size() - 1; i >= 0; i--)
	{
		delete list_modules[i];
		list_modules[i] = nullptr;
	}
	list_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	LOG("Application Init --------------");
	for (size_t i = 0; i < list_modules.size(); i++)
	{
		ret = list_modules[i]->Init();
	}

	LOG("Application Start --------------");
	for (size_t i = 0; i < list_modules.size(); i++)
	{
		ret = list_modules[i]->Start();
	}


return ret;
}

void Application::PreUpdate()
{
	if (gameState == GameState::PLAY) dtG = dt * timeSpeed;
	else dtG = 0;
}


update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();

	for (size_t i = 0; i < list_modules.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = list_modules[i]->PreUpdate(dt);
	}

	for (size_t i = 0; i < list_modules.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = list_modules[i]->Update(dt);
	}

	for (size_t i = 0; i < list_modules.size() && ret == UPDATE_CONTINUE; i++)
	{
		ret = list_modules[i]->PostUpdate(dt);
	}

	return ret;
}

void Application::SetDT(float dt)
{
	this->dt = dt;
}
float Application::DTG()
{
	return dtG;
}
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = list_modules.size() - 1; i >= 0; i--)
	{
		list_modules[i]->CleanUp();
		delete list_modules[i];
		list_modules[i] = nullptr;
	}
	list_modules.clear();

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}