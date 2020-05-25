#include <stdlib.h>
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

#include "components/monitoring/framerate.window.h"

// Catch Main Window Events
void WindowResizeCallback( GLFWwindow* window, int width, int height ) {
    std::cout << "Resize handled!" << std::endl;
}
void WindowPosCallback( GLFWwindow* window, int xpos, int ypos ) {
    std::cout << "Window position change handled!" << std::endl;
}
void KeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    std::cout << "Key has been handled! " << key << " mode: " << action << std::endl;
    ImGui_ImplGlfw_KeyCallback( window, key, scancode, action, mods );
}
void CharCallback( GLFWwindow* window, unsigned int character )
{
    ImGui_ImplGlfw_CharCallback( window, character );
}
void MouseButtonCallback( GLFWwindow* window, int button, int action, int mods )
{
    ImGui_ImplGlfw_MouseButtonCallback( window, button, action, mods );
}
void MousePosCallback( GLFWwindow* window, double x, double y ) {  }
void MouseWheelCallback( GLFWwindow* window, double x, double y )
{
    ImGui_ImplGlfw_ScrollCallback( window, x, y );
}

// Measure speed
void measureSpeed(int &frameCount, double &currentTime, double &previousTime, int &frameRate, double &frameTime) {
    currentTime = glfwGetTime();
    frameCount++;

    // If a second has passed.
    if ( currentTime - previousTime >= 1.0 )
    {
        frameRate = frameCount;
        frameTime = 1000.0/double(frameCount);
        frameCount = 0;
        previousTime = currentTime;
    }
}

int main( int argc, const char * argv[] )
{
    // Check GLFW
    if (!glfwInit()) {
		std::cout << "GLFW not initialized." << std::endl;
        exit(1);
    }
    
    // Check Vulkan
    if (!glfwVulkanSupported())
    {
        std::cout << "Vulkan API is not available!" << std::endl;
        exit(1);
    }

    // Create Main Window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "This is a simple GLFW Example", NULL, NULL);
    glfwMakeContextCurrent(window); // Set context
    glfwSwapInterval(1); // Enable vsync

    // Set window callbacks
    glfwSetWindowSizeCallback( window, WindowResizeCallback );
    glfwSetWindowPosCallback( window, WindowPosCallback );
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCharCallback( window, CharCallback );
    glfwSetMouseButtonCallback( window, MouseButtonCallback );
    glfwSetCursorPosCallback( window, MousePosCallback );
    glfwSetScrollCallback( window, MouseWheelCallback );

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Init OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, false);
    ImGui_ImplOpenGL2_Init();

    // Setup style
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.Fonts->AddFontFromFileTTF("resources/verdana.ttf", 16.0f, NULL, NULL);

    ImGuiStyle &style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;
    style.WindowPadding = ImVec2(6, 6);
    style.FrameBorderSize = 1.0f;
    style.TabBorderSize = 1.0f;
    style.WindowRounding = 2.0f;
    style.FrameRounding = 2.0f;
    style.TabRounding = 2.0f;
    style.GrabRounding = 2.0f;
    style.ChildRounding = 2.0f;
    style.PopupRounding = 2.0f;
    style.WindowMenuButtonPosition = ImGuiDir_Right;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.ScrollbarRounding = 2.0f;
    style.FramePadding = ImVec2(10, 6);
    style.ItemSpacing = ImVec2(10, 6);
    style.ItemInnerSpacing = ImVec2(10, 6);
    style.GrabMinSize = 14.0f;
	colors[ImGuiCol_Text] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.500f, 0.500f, 0.500f, 1.000f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.180f, 0.180f, 0.180f, 1.000f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.280f, 0.280f, 0.280f, 0.000f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
	colors[ImGuiCol_Border] = ImVec4(0.266f, 0.266f, 0.266f, 1.000f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.200f, 0.200f, 0.200f, 1.000f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.280f, 0.280f, 0.280f, 1.000f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.148f, 0.148f, 0.148f, 1.000f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.160f, 0.160f, 0.160f, 1.000f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.277f, 0.277f, 0.277f, 1.000f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.300f, 0.300f, 0.300f, 1.000f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 1.000f, 1.000f, 1.000f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_Button] = ImVec4(1.000f, 1.000f, 1.000f, 0.000f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
	colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.391f);
	colors[ImGuiCol_Header] = ImVec4(0.313f, 0.313f, 0.313f, 1.000f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
	colors[ImGuiCol_Separator] = colors[ImGuiCol_Border];
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.391f, 0.391f, 0.391f, 1.000f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(1.000f, 1.000f, 1.000f, 0.250f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.670f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_Tab] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.352f, 0.352f, 0.352f, 1.000f);
	colors[ImGuiCol_TabActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.098f, 0.098f, 0.098f, 1.000f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.195f, 0.195f, 0.195f, 1.000f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.469f, 0.469f, 0.469f, 1.000f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.586f, 0.586f, 0.586f, 1.000f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 1.000f, 1.000f, 0.156f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.000f, 0.391f, 0.000f, 1.000f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.586f);

    std::cout << "The application is ready to loop!" << std::endl;

    double previousTime = glfwGetTime();
    double currentTime = 0;
    int frameCount = 0;
    int frameRate = 0;
    double frameTime = 0;

    ImVec4 clear_color = ImColor(0, 0, 0);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // --- Monitoring ---

        // Measure speed
        measureSpeed(frameCount, currentTime, previousTime, frameRate, frameTime);

        // --- Logistic ---

        // Start the Dear ImGui frame
        {
            ImGui_ImplOpenGL2_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            Monitoring::RenderFramerateWindow(frameRate, frameTime);
            Monitoring::RenderTimelineWindow();

            ImGui::ShowDemoWindow();
        }

        // --- Rendering ---
        {
            glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui::Render();
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }
    }

    // Cleanup the program
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}

