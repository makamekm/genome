#include <imgui.h>
#include <GLFW/glfw3.h>
#include "../monitoring/framerate.window.h"

namespace Development {
	void Init()
	{
		// Nothing yet
	}

	void Loop(const int &frameRate, const double &frameTime)
	{
    Monitoring::RenderFramerateWindow(frameRate, frameTime);
    Monitoring::RenderTimelineWindow();
    ImGui::ShowDemoWindow();
	}

	void Render(const int &frameRate, const double &frameTime)
	{
		// Nothing yet
	}
}