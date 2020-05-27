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
    TaskManager(const unsigned int &nonFramedThreads = 1, const unsigned int &framedThreads = 1);
    int GetLastFrameGpuProfilerData();
    int GetLastFrameCpuProfilerData();
    int GetThreadsCount();
    void EndFrame();
    void BeginFrame(const double& framePassedTime);
    void Render();
    void Destroy();
    void Start();
    void End();
    unsigned int AddJobToIndex(
      std::function<void(const double &time)> job,
      const unsigned int &preferedIndex = 0,
      const bool &nonFramedThread = false
    );
    unsigned int AddJob(
      std::function<void(const double &time)> job,
      const bool &nonFramedThread = false
    );
    void RemoveJob(
      const unsigned int &jobId
    );
};