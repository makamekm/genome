#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <functional>
#include <GLFW/glfw3.h>
#include "task-manager.h"

static bool isRunning = false;
static double framePassedTime = 0.0f;

unsigned int getRandomId() {
  return ((UINT32_MAX - 1) * (rand()/(double)RAND_MAX) );
}

struct Job {
  unsigned int id;
  std::function<void(const double& time)> fn;
};

class WorkerThread {
  private:
    std::thread thread;
    double previousTime = glfwGetTime();

  public:
    WorkerThread(int index):
      index(index),
      manual(true) {
      }
    WorkerThread() {
      }

    std::mutex m;
    std::condition_variable cv;
    bool nonFramedThread = false;
    bool readyToExecute = false;
    bool processed = true;
    unsigned int index = 0;
    bool manual = false;
    std::vector<Job> jobs;

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
          job.fn(timePassed);
        }
        previousTime = nowTime;
        readyToExecute = false;
        processed = true;
        cv.notify_one();
      }
      // std::cout << "Thread stopped: " << index << std::endl;
    }

    unsigned int AddJob(std::function<void(const double& time)> job) {
      Job j;
      j.id = getRandomId();
      j.fn = job;
      jobs.push_back(j);
      return j.id;
    }

    void RemoveJob(const unsigned int& id) {
      std::vector<Job>::iterator position = std::find_if(jobs.begin(), jobs.end(), [id](Job &j){
        return j.id == id;
      });
      if (position != jobs.end()) {
        jobs.erase(position);
      }
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

void createThreads(const unsigned int &nonFramedThreads, const unsigned int &framedThreads) {
  threads = new WorkerThread*[threadsCount];

  for (unsigned int i = 0; i < nonFramedThreads; i++) {
    threads[i] = new WorkerThread(i);
    threads[i]->nonFramedThread = true;
  }

  for (unsigned int i = 0; i < framedThreads; i++) {
    threads[i + nonFramedThreads] = new WorkerThread(i);
    threads[i + nonFramedThreads]->nonFramedThread = true;
  }

  for (unsigned int i = nonFramedThreads + framedThreads; i < threadsCount; i++) {
    threads[i] = new WorkerThread();
  }
} 

TaskManager::TaskManager(const unsigned int &nonFramedThreads, const unsigned int &framedThreads) {
  countThreads();
  createThreads(nonFramedThreads, framedThreads);

  auto id = this->AddJob([](const double& time) {
    // std::cout << "Hi from thread!" << workerIndex << std::endl;
  });
}

int TaskManager::GetThreadsCount() {
  return threadsCount;
}

unsigned int TaskManager::AddJob(
  std::function<void(const double& time)> job,
  const bool &nonFramedThread
) {
  std::vector<WorkerThread*> candidates;

  for (unsigned int i = 0; i < threadsCount; i++) {
    if (!threads[i]->manual && threads[i]->nonFramedThread == nonFramedThread) {
      candidates.push_back(threads[i]);
    }
  }

  std::sort(candidates.begin(), candidates.end(), [](WorkerThread *a, WorkerThread *b){
    return a->jobs.size() < b->jobs.size(); 
  });

  if (candidates.size() > 0) {
    return candidates.at(0)->AddJob(job);
  } else {
    std::cout << "Job has not been pushed!" << std::endl;
  }

  return 0;
}

unsigned int TaskManager::AddJobToIndex(
  std::function<void(const double& time)> job,
  const unsigned int &preferedIndex,
  const bool &nonFramedThread
) {
  for (unsigned int i = 0; i < threadsCount; i++) {
    if (threads[i]->manual && threads[i]->nonFramedThread == nonFramedThread && threads[i]->index) {
      return threads[i]->AddJob(job);
    }
  }

  std::cout << "Job has not been pushed!" << std::endl;

  return 0;
}

void TaskManager::RemoveJob(const unsigned int &id) {
  for (unsigned int i = 0; i < threadsCount; i++) {
    threads[i]->RemoveJob(id);
  }
}

int TaskManager::GetLastFrameGpuProfilerData() {
  return 0;
}

int TaskManager::GetLastFrameCpuProfilerData() {
  return 0;
}

void TaskManager::EndFrame() {
  for (int i = 0; i < threadsCount; i++) {
    if (!threads[i]->nonFramedThread) {
      std::unique_lock<std::mutex> lk(threads[i]->m);
      threads[i]->cv.wait(lk, [&]{
        return threads[i]->processed;
      });
    }
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