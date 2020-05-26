#pragma once

#include "../components/task-manager/task-manager.h"

namespace Production {
  TaskManager* GetTaskManager();

  // Init Production
  void Init();

  // Destroy Production
  void Destroy();

  // After Loop Production
  void Finish();

  // Loop Production
  void Loop(const double &frameTime);

  // Render Production
  void Render();
}