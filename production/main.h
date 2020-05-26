#pragma once

#include "../components/task-manager/task-manager.h"

namespace Production {
  TaskManager* GetTaskManager();

  // Init Production
  void Init();

  // Destroy Production
  void Destroy();

  // After Loop Production
  void FinishLoop();

  // Loop Production
  void StartLoop(const double &frameTime);

  // Render Production
  void Render();
}