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
	}

	void Destroy()
	{
		delete taskManager;
	}

	void Finish()
	{
		taskManager->EndFrame();
	}

	void Loop(const int &frameRate, const double &frameTime)
	{
		taskManager->BeginFrame();
	}

	void Render()
	{
		taskManager->Render();
	}
}