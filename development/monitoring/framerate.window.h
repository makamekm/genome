namespace Monitoring {
  // Render IMGUI framerate window
  void RenderFramerateWindow(const int &frameRate, const double &frameTime, const char* name = "Monitoring::Framerate");

  // Render IMGUI timeline window
  void RenderCPUAndMemoryWindow(const char* name = "Monitoring::CPU & Memory");

  // Render IMGUI timeline window
  void RenderTimelineWindow(const char* name = "Monitoring::Timeline");
}