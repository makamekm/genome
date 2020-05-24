#include <stdlib.h>

// imgui headers
#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

#include <GLFW/glfw3.h>

bool RCCppInit();
void RCCppCleanup();
void RCCppUpdate();

void WindowResizeCallback( GLFWwindow* window, int width, int height ){  }
void WindowPosCallback( GLFWwindow* window, int xpos, int ypos ){  }
void KeyCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
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
void MousePosCallback( GLFWwindow* window, double x, double y ){  }
void MouseWheelCallback( GLFWwindow* window, double x, double y )
{
    ImGui_ImplGlfw_ScrollCallback( window, x, y );
}

int main( int argc, const char * argv[] )
{
    if (!glfwInit())
        exit(1);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "This is a simple GLFW Example", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Power save - ensure callbacks point to the correct place
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

    ImVec4 clear_color = ImColor(114, 144, 154);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(50,400), ImGuiCond_Appearing );
        ImGui::SetNextWindowSize(ImVec2(0,0), ImGuiCond_Always );
        ImGui::Begin("RCCppMainLoop Window" );
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

