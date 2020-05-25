#pragma once

#include "../components/task-manager/task-manager.h"

namespace Production {
  TaskManager* GetTaskManager();

  // Init Production
  void Init();

  // Destroy Production
  void Destroy();

  // After Loop Production
  void AfterLoop();

  // Loop Production
  void Loop(const int &frameRate, const double &frameTime);

  // Render Production
  void Render();
}