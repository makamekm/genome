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
    ImGui::StyleColorsClassic();

    std::cout << "The application is ready to loop!" << std::endl;

    double previousTime = glfwGetTime();
    double currentTime = 0;
    int frameCount = 0;
    int frameRate = 0;
    double frameTime = 0;

    ImVec4 clear_color = ImColor(50, 50, 50);
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

