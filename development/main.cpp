#include <imgui.h>
#include <GLFW/glfw3.h>
#include "./monitoring/framerate.window.h"
#include "./monitoring/profiler.window.h"
#include "../components/colors/colors.h"
#include "../components/task-manager/task-manager.h"
#include "../production/main.h"

namespace Development {
	ImGuiUtils::ProfilersWindow *profiler;

	void Init()
	{
		profiler = new ImGuiUtils::ProfilersWindow();
	}

	void Destroy()
	{
		delete profiler;
	}

	void AfterLoop()
	{
		// Nothing here
	}

	void Loop(const int &frameRate, const double &frameTime)
	{
    Monitoring::RenderFramerateWindow(frameRate, frameTime);
    Monitoring::RenderTimelineWindow();
    ImGui::ShowDemoWindow();

		// auto& gpuProfilerData = Production::taskManager->GetLastFrameGpuProfilerData();
		// auto& cpuProfilerData = Production::taskManager->GetLastFrameCpuProfilerData();

		// profiler->gpuGraph.LoadFrameData(gpuProfilerData.data(), gpuProfilerData.size());
		// profiler->cpuGraph.LoadFrameData(cpuProfilerData.data(), cpuProfilerData.size());

		profiler->Render();
	}

	void Render()
	{
		// Nothing yet
	}
}