#include <imgui.h>
#include <GLFW/glfw3.h>
#include "../plot-var/plot-var.h"

namespace Monitoring {
	void RenderFramerateWindow(const int &frameRate, const double &frameTime)
	{
		ImGui::SetNextWindowPos(ImVec2(10,10), ImGuiCond_Appearing );
		ImGui::SetNextWindowSize(ImVec2(300,0), ImGuiCond_Always );
		ImGui::Begin("Monitoring::Framerate");
		ImGui::PlotVar("FPS", frameRate, 0, 60);
		ImGui::PlotVar("Frame Time", frameTime, 0);
		ImGui::End();
	}

	void RenderTimelineWindow()
	{
		double currentTime = glfwGetTime();
		ImGui::SetNextWindowPos(ImVec2(10,135), ImGuiCond_Appearing );
		ImGui::SetNextWindowSize(ImVec2(300,0), ImGuiCond_Always );
		ImGui::Begin("Monitoring::Timeline");
		ImGui::Text("%s: %-3.4f", "Global Time", currentTime);
		ImGui::End();
	}
}