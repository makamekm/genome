#include <stdlib.h>
#include <string>

#pragma once

struct TaskProfile {
  double startTime;
  double endTime;
  std::string name;
  uint32_t color;
  double GetLength()
  {
    return endTime - startTime;
  }
};

class TaskManager {
  public:
    TaskManager();
    int GetLastFrameGpuProfilerData();
    int GetLastFrameCpuProfilerData();
    int GetThreadsCount();
    void EndFrame();
    void BeginFrame(const double& framePassedTime);
    void Render();
    void Destroy();
    void Start();
    void End();
};