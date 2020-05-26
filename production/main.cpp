#include <imgui.h>
#include <GLFW/glfw3.h>

#include "main.h"
#include "../components/task-manager/task-manager.h"

namespace Production {
  TaskManager *taskManager;

	TaskManager* GetTaskManager()
	{
		return taskManager;
	}

	void Init()
	{
		taskManager = new TaskManager();
		taskManager->Start();
	}

	void Destroy()
	{
		taskManager->End();
		taskManager->Destroy();
		delete taskManager;
	}

	void FinishLoop()
	{
		taskManager->EndFrame();
	}

	void StartLoop(const double &framePassedTime)
	{
		taskManager->BeginFrame(framePassedTime);
	}

	void Render()
	{
		taskManager->Render();
	}
}