#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <iostream>
#include <functional>
#include <GLFW/glfw3.h>
#include "task-manager.h"

static bool isRunning = false;
static double framePassedTime = 0.0f;

class WorkerThread {
  // int[10] coroutines;
  private:
  unsigned int index = 0;
  std::thread thread;
  std::vector<std::function<void(double time)>> jobs;
  double previousTime = glfwGetTime();

  public:
    WorkerThread(int index):
      index(index) {
      }

    std::mutex m;
    std::condition_variable cv;
    bool nonFramedThread = false;
    bool readyToExecute = false;
    bool processed = true;

    void Run() {
      thread = std::thread(&WorkerThread::RunTask, this);
    }

    void RunTask() {
      // std::cout << "Thread started: " << index << std::endl;
      while (isRunning) {
        if (!nonFramedThread) {
          std::unique_lock<std::mutex> lk(m);
          cv.wait(lk, [&]{
            return readyToExecute;
          });
        }
        processed = false;
        double nowTime = glfwGetTime();
        double timePassed = nowTime - previousTime;
        for (auto& job : jobs) {
          job(timePassed);
        }
        previousTime = nowTime;
        readyToExecute = false;
        processed = true;
      }
      // std::cout << "Thread stopped: " << index << std::endl;
    }

    void AddJob(std::function<void(double time)> job) {
      jobs.push_back(job);
    }
};

static WorkerThread** threads;
static unsigned int threadsCount = 0;

void countThreads() {
  threadsCount = std::thread::hardware_concurrency();
  std::cout << "Threads awailable: " << threadsCount << std::endl;

  if (threadsCount < 2) {
    std::cout << "Your system does not have enough amount of threads, minimum is 2, but you have " << threadsCount << std::endl;
    exit(2);
  }
} 

void createThreads() {
  threads = new WorkerThread*[threadsCount];

  for (unsigned int i = 0; i < threadsCount; i++) {
    threads[i] = new WorkerThread(i);
  }
} 

TaskManager::TaskManager() {
  countThreads();
  createThreads();

  threads[0]->AddJob([](double passed) {
    // std::cout << "Hi from thread!" << passed << std::endl;
  });
}

int TaskManager::GetThreadsCount() {
  return threadsCount;
}

int TaskManager::GetLastFrameGpuProfilerData() {
  return 0;
}

int TaskManager::GetLastFrameCpuProfilerData() {
  return 0;
}

void TaskManager::EndFrame() {
  for (int i = 0; i < threadsCount; i++) {
    std::unique_lock<std::mutex> lk(threads[i]->m);
    threads[i]->cv.wait(lk, [&]{
      return threads[i]->processed;
    });
  }
}

void TaskManager::BeginFrame(const double& frameTime) {
  framePassedTime = frameTime;
  for (int i = 0; i < threadsCount; i++) {
    std::lock_guard<std::mutex> lk(threads[i]->m);
    threads[i]->readyToExecute = true;
    threads[i]->cv.notify_one();
  }
}

void TaskManager::Render() {

}

void TaskManager::Start() {
  isRunning = true;
  for (unsigned int i = 0; i < threadsCount; i++) {
    threads[i]->Run();
  }
}

void TaskManager::End() {
  isRunning = false;
}

void TaskManager::Destroy() {
  for (int i = 0; i < threadsCount; i++) {
    delete threads[i];
  }
  delete threads;
}