#include <imgui.h>
#include <GLFW/glfw3.h>
#include "./monitoring/framerate.window.h"
#include "./monitoring/profiler.window.h"
#include "../components/colors/colors.h"
#include "../components/task-manager/task-manager.h"
#include "../production/main.h"

double previousTime = glfwGetTime();
double currentTime = 0;
int frameCount = 0;
int frameRate = 0;
double frameTime = 0;

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

	void FinishLoop()
	{
		// Nothing here
	}

	void StartLoop(const double &framePassedTime)
	{
		measureSpeed(frameCount, currentTime, previousTime, frameRate, frameTime);
    Monitoring::RenderFramerateWindow(frameRate, frameTime);
    Monitoring::RenderCPUAndMemoryWindow();
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