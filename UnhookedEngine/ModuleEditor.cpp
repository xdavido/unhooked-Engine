#include "ModuleEditor.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "SDL/include/SDL_opengl_glext.h"


ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
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

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);
    ImGui_ImplOpenGL3_Init();

    return true;
}

void ModuleEditor::Draw()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    MainMenuBar();

    SettingsMenu();

    if (OpenAbout == true)
    {
        if (ImGui::Begin("About Uss"))
        {
            ImGui::SeparatorText("ABOUT UNHOOKED ENGINE:");
            ImGui::Text("Unhooked Engine v.0.1");
            ImGui::Text("The new 3D Game Engine under CITM development");
            ImGui::Text("David Ruiz Luengo & Pau Garriga Brotons");
            ImGui::Text("3rd party Libraries:");

            ImGui::End();
        }
    }

    //ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui::EndFrame();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool ModuleEditor::CleanUp()
{
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

void ModuleEditor::MainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::Button("Exit"))
        {
            App->renderer3D->TurnOff = true;
        }

        if (ImGui::BeginMenu("Menu"))
        {
            ImGui::Text("ToDo");
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
            {
                OpenAbout = !OpenAbout;
            }

            if (ImGui::MenuItem("GitHub"))
            {
                ShellExecute(NULL, "open", "https://github.com/xdavido/unhooked-Engine", 0, 0, SW_SHOWNORMAL);

            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void ModuleEditor::SettingsMenu()
{
    if (ImGui::Begin("Settings"))
    {
        ImGui::PlotHistogram("FPS", mFPSLog.data(), mFPSLog.size(), 2, lastValue);

        if (ImGui::CollapsingHeader("LOG"))
        {
            ImGui::SeparatorText("OPEN GL:");
            ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
            ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));
            ImGui::Text("OpenGL version supported %s", glGetString(GL_VERSION));
            ImGui::Text("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Console");

            ImGui::BeginChild("Scrolling");
            for (size_t i = 0; i < MSG.size(); i++)
            {
                ImGui::TextColored(ImVec4(0.78, 1, 1, 1), "%s", MSG.at(i).data());
            }
            ImGui::EndChild();
        }

        if (ImGui::CollapsingHeader("Render Options"))
        {
            if (ImGui::Checkbox("GL_DEPTH_TEST", &gl_DEPTH_TEST))
            {
                if (gl_DEPTH_TEST)
                {
                    glEnable(GL_DEPTH_TEST);
                    MSG.push_back("GL_DEPTH_TEST Enabled");
                }
                else
                {
                    glDisable(GL_DEPTH_TEST);
                    MSG.push_back("GL_DEPTH_TEST Disabled");
                }
            }
            if (ImGui::Checkbox("GL_CULL_FACE", &gl_CULL_FACE))
            {
                if (gl_CULL_FACE)
                {
                    glEnable(GL_CULL_FACE);
                    MSG.push_back("GL_CULL_FACE Enabled");
                }
                else
                {
                    glDisable(GL_CULL_FACE);
                    MSG.push_back("GL_CULL_FACE Disabled");
                }
            }
            if (ImGui::Checkbox("GL_LIGHTING", &gl_LIGHTING))
            {
                if (gl_LIGHTING)
                {
                    glEnable(GL_LIGHTING);
                    MSG.push_back("GL_LIGHTING Enabled");
                }
                else
                {
                    glDisable(GL_LIGHTING);
                    MSG.push_back("GL_LIGHTING Disabled");
                }
            }
            if (ImGui::Checkbox("GL_COLOR_MATERIAL", &gl_COLOR_MATERIAL))
            {
                if (gl_COLOR_MATERIAL)
                {
                    glEnable(GL_COLOR_MATERIAL);
                    MSG.push_back("GL_COLOR_MATERIAL Enabled");
                }
                else
                {
                    glDisable(GL_COLOR_MATERIAL);
                    MSG.push_back("GL_COLOR_MATERIAL Disabled");
                }
            }
            if (ImGui::Checkbox("GL_TEXTURE_2D", &gl_TEXTURE_2D))
            {
                if (gl_TEXTURE_2D)
                {
                    glEnable(GL_TEXTURE_2D);
                    MSG.push_back("GL_TEXTURE_2D Enabled");
                }
                else
                {
                    glDisable(GL_TEXTURE_2D);
                    MSG.push_back("GL_TEXTURE_2D Disabled");
                }
            }
            if (ImGui::Checkbox("Wireframe Mode", &wireframe))
            {
                SetWireFrameMode(wireframe);
            }
            //ImGui::Checkbox("Vsync", &vsync);
            //SetVsync(vsync);
            
        }

        if (ImGui::CollapsingHeader("Window Settings"))
        {
            ImGui::SeparatorText("Window");

            ImGui::SliderInt("Height", &Height, 144, 1080);
            ImGui::SliderInt("Width", &Width, 256, 1920);

            ImGui::Checkbox("FullScreen", &fullscreen);
            ImGui::Checkbox("Resizable", &resizable);
            ImGui::Checkbox("Borderless", &borderless);
            ImGui::Checkbox("FullScreen Desktop", &fullscreendesktop);

            if (ImGui::Button("Apply Changes"))
            {
                App->window->SetNewWindow(Height, Width, fullscreen, resizable, borderless, fullscreendesktop);
                MSG.push_back("Window Changes Applied");
            }

            ImGui::SeparatorText("Background Color");

            ImGui::SliderFloat("Red", &color.r, 0, 255);
            ImGui::SliderFloat("Green", &color.g, 0, 255);
            ImGui::SliderFloat("Blue", &color.b, 0, 255);
            App->renderer3D->ChangeColorScene(color);
        }

        // Button Save/Load
        ImGui::AlignTextToFramePadding();
        if (ImGui::Button("Save"))
        {
            MSG.push_back("Boton Pulsado");
        }ImGui::SameLine();
        ImGui::Button("Load");

    }
    ImGui::End();
}

void ModuleEditor::AddFPS(float aFPS)
{
    if (mFPSLog.size() < 30)
    {
        mFPSLog.push_back(aFPS);
    }
    else
    {
        mFPSLog.erase(mFPSLog.begin());
        mFPSLog.push_back(aFPS);
    }
}

void ModuleEditor::SetWireFrameMode(bool wireframe)
{
    if (wireframe)
    {
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);

    }
    else
    {
        glPolygonMode(GL_FRONT, GL_LINE);
        glPolygonMode(GL_BACK, GL_LINE);
    }
}