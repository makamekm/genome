#include <stdlib.h>
#include <iostream>

// #define GLFW_INCLUDE_VULKAN
// #include <vulkan/vulkan.h>
// #include <vulkan/vulkan_core.h>
// #include <vulkan/vk_platform.h>
// #include <vulkan/vk_sdk_platform.h>
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

// #define GLM_FORCE_RADIANS
// #define GLM_FORCE_DEPTH_ZERO_TO_ONE
// #include <glm/vec4.hpp>
// #include <glm/mat4x4.hpp>

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"

#ifdef DEVELOPMENT_MODE
#include "development/main.h"
#endif

#include "production/main.h"

#include "components/style/style.h"

// static char const * AppName = "01_InitInstance";
// static char const * EngineName = "Vulkan.hpp";

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
void measureSpeed(double &currentTime, double &previousPassedTime, double &framePassedTime) {
    currentTime = glfwGetTime();
    framePassedTime = currentTime - previousPassedTime;
    previousPassedTime = currentTime;
}

VkInstance instance;

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

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;
    
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    // uint32_t extensionCount = 0;
    // vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    // std::cout << extensionCount << " extensions supported\n";

	// glfwDefaultWindowHints();
	// glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Comment out this if you need OpenGL also

    // Create Main Window
    // GLFWwindow* window = glfwCreateWindow(1280, 720, "This is a simple GLFW Example", glfwGetPrimaryMonitor(), NULL);
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
    ImGui::SetDarkTheme();

    std::cout << "The application is ready to loop!" << std::endl;

    double previousPassedTime = glfwGetTime();
    double currentTime = 0;
    double framePassedTime = 0;

    ImVec4 clear_color = ImColor(0, 0, 0);

    #ifdef DEVELOPMENT_MODE
    Development::Init();
    #endif

    Production::Init();

    while (!glfwWindowShouldClose(window))
    {
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED))
        {
            glfwWaitEvents();
            continue;
        }

        glfwPollEvents();

        // --- Monitoring ---

        measureSpeed(currentTime, previousPassedTime, framePassedTime);

        // Start the Dear ImGui frame
        {
            ImGui_ImplOpenGL2_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        // --- Loop ---

        Production::StartLoop(framePassedTime);

        // Run Loop
        #ifdef DEVELOPMENT_MODE
        Development::StartLoop(framePassedTime);
        #endif

        Production::FinishLoop();

        #ifdef DEVELOPMENT_MODE
        Development::FinishLoop();
        #endif

        // --- Render ---
        {
            glViewport(0, 0, (int)ImGui::GetIO().DisplaySize.x, (int)ImGui::GetIO().DisplaySize.y);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT);

            Production::Render();

            #ifdef DEVELOPMENT_MODE
            Development::Render();
            #endif

            ImGui::Render();
            ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(window);
        }
    }

    // --- Cleanup ---

    Production::Destroy();

    #ifdef DEVELOPMENT_MODE
    Development::Destroy();
    #endif


	// vkDestroySurfaceKHR((VkInstance)instanceCreateInfo, VkSurfaceKHR(surf), nullptr); //vkcpp seems have no destructor for surface object
    vkDestroyInstance(instance, nullptr);
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();

    return 0;
}

