#include "ModuleEditor.h"
#include "imgui/imgui.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
#include "Application.h"
#include "Modulewindow.h"
#include "ModuleRenderer3D.h"


ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app , start_enabled)
{

}

ModuleEditor::~ModuleEditor()
{

}

bool ModuleEditor::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
 
	ImGui::StyleColorsLight();

	
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
	ImGui_ImplOpenGL3_Init();


 return false;
}

void ModuleEditor::DrawEdior()
{
	ImGui_ImplSDL2_NewFrame();
}