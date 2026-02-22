#include "gui.hpp"

static const char* glsl_version = "#version 410";

void GUI::init(GLFWwindow* window){
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void GUI::beginFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUI::render(){
    ImGui::SetNextWindowSize(ImVec2(200, 160), ImGuiCond_Always);
    ImGui::Begin("ICP Debug Panel");

    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Separator();

    ImGui::Text("OpenGL: %s", glGetString(GL_VERSION));
    ImGui::Text("Renderer: %s", glGetString(GL_RENDERER));

    GLint profile;
    glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);

    const char* profileStr = "Unknown";
    if (profile & GL_CONTEXT_CORE_PROFILE_BIT)
        profileStr = "Core";
    else if (profile & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
        profileStr = "Compatibility";

    ImGui::Text("Profile: %s", profileStr);

    ImGui::Text("Fullscreen: %s", Renderer::isFullscreen() ? "YES" : "NO");
    ImGui::Text("VSync: %s", Renderer::isVSync() ? "ON" : "OFF");
    ImGui::Text("MSAA: %s", Renderer::isMSAA() ? "ON" : "OFF");

    ImGui::End();
}

void GUI::endFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}