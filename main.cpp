#include <stdlib.h>
#include <iostream>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

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

int main( int argc, const char * argv[] )
{
    if (!glfwInit()) {
		std::cout << "GLFW not initialized." << std::endl;
        exit(1);
    }
    
    if (!glfwVulkanSupported())
    {
        std::cout << "Vulcan is not available!" << std::endl;
        exit(1);
    }

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

    ImGui_ImplGlfw_InitForOpenGL(window, false);
    ImGui_ImplOpenGL2_Init();

    // Setup style
    ImGui::StyleColorsDark();

    std::cout << "The application is ready to loop!" << std::endl;

    ImVec4 clear_color = ImColor(50, 50, 50);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(50,400), ImGuiCond_Appearing );
        ImGui::SetNextWindowSize(ImVec2(0,0), ImGuiCond_Always );
        ImGui::Begin("The Development Window" );
        ImGui::Text("You can change Window's code at runtime!");
        ImGui::End();

        // Rendering
        {
            glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui::Render();
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }
    }

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}

