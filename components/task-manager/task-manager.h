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
    int GetLastFrameGpuProfilerData();
    int GetLastFrameCpuProfilerData();
    void EndFrame();
    void BeginFrame();
    void Render();
};