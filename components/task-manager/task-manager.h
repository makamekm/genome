#include <stdlib.h>
#include <string>
#include <functional>

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
    TaskManager(unsigned int nonFramedThreads = 1);
    int GetLastFrameGpuProfilerData();
    int GetLastFrameCpuProfilerData();
    int GetThreadsCount();
    void EndFrame();
    void BeginFrame(const double& framePassedTime);
    void Render();
    void Destroy();
    void Start();
    void End();
    unsigned int AddJob(
      std::function<void(const double &time, const unsigned int &workerIndex)> job,
      const unsigned int &preferedIndex = 0,
      const bool &nonFramedThread = false
    );
    void RemoveJob(
      const unsigned int &jobId
    );
};