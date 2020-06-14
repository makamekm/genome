// #include <fstream>
#include <iostream>
// #include <unistd.h>
#include <imgui.h>
#include <GLFW/glfw3.h>
#include "../plot-var/plot-var.h"

namespace Monitoring {
	// double vm, rss;

	// void process_mem_usage(double& vm_usage, double& resident_set)
	// {
	// 	vm_usage     = 0.0;
	// 	resident_set = 0.0;

	// 	// the two fields we want
	// 	unsigned long vsize;
	// 	long rss;
	// 	{
	// 		std::string ignore;
	// 		std::ifstream ifs("/proc/self/stat", std::ios_base::in);
	// 		ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
	// 						>> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
	// 						>> ignore >> ignore >> vsize >> rss;
	// 	}
	// 	long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
	// 	vm_usage = vsize / 1024.0 / 1000.0 / 1000.0 / 1000.0 / 1000.0;
	// 	resident_set = rss * page_size_kb / 1000.0 / 1000.0 / 1000.0 / 1000.0 / 1000.0 / 8;
	// }

	void RenderFramerateWindow(const int &frameRate, const double &frameTime, const char* name)
	{
		ImGui::SetNextWindowPos(ImVec2(10,10), ImGuiCond_FirstUseEver );
		ImGui::SetNextWindowSize(ImVec2(300,0), ImGuiCond_Always );
		ImGui::Begin(name);
		ImGui::PlotVar("FPS", frameRate, 0, 60);
		ImGui::PlotVar("Frame Time", frameTime, 0);
		ImGui::End();
	}

	void RenderCPUAndMemoryWindow(const char* name)
	{
   	// process_mem_usage(vm, rss);
		ImGui::SetNextWindowPos(ImVec2(10,135), ImGuiCond_FirstUseEver );
		ImGui::SetNextWindowSize(ImVec2(300,0), ImGuiCond_Always );
		ImGui::Begin(name);
		ImGui::Text("WIP");
		// ImGui::PlotVar("RAM [MB]", rss, 0);
		// ImGui::PlotVar("RAM [%]", rss / vm * 100, 0);
		ImGui::End();
	}

	void RenderTimelineWindow(const char* name)
	{
		double currentTime = glfwGetTime();
		ImGui::SetNextWindowPos(ImVec2(10,135), ImGuiCond_FirstUseEver );
		ImGui::SetNextWindowSize(ImVec2(300,0), ImGuiCond_Always );
		ImGui::Begin(name);
		ImGui::Text("%s: %-3.4f", "Global Time", currentTime);
		ImGui::End();
	}
}