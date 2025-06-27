#include <iostream>
#include <chrono>
#include <thread>

class Window;
class InputManager;
class TimeManager;

class Application {
  private: 
    static Application* instance;
    bool isRunning;
    Window* window;
    InputManager* inputManager;
    TimeManager* timeManager;

  public:
    static Application& GetInstance() {
      if(!instance) {
        instance = new Application();
      }
      return *instance;
    }

    bool Initialize() {
      std::cout << "Initialize Application..." << std::endl;

      // Window
      if(!CreateWindow(800, 600, "Blink Game Engine")) {
        std::cout << "Failed to create window!" << std::endl;
        return false;
      }

      // Input system
      if(!InitializeInput()) {
        std::cout << "Failed to initialize input!" << std::endl;
        return false;
      }

      // Time management
      if(!InitializeTime()){
        std::cout << "Failed to initialize time management!" << std::endl;
        return false;
      }

      isRunning = true;
      std::cout << "Application initialized successfully!" << std::endl;
      return true;
    }

    void Run() {
      std::cout << "Starting main game loop..." << std::endl;

      while (IsRunning()) {
        ProcessInput();
        float deltaTime = UpdateTime();
        Update(deltaTime);
        Render();
        PresentFrame();

        // Simple frame rate limiting: (16ms = ~60 FPS)
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
      }

      std::cout << "Exiting main game loop..." << std::endl;
    }

    void Shutdown() {
      std::cout << "Shutting down Application" << std::endl;

      // Cleanup in reverse order of initialization
      // ShutdownTime();
      // ShutdownInput();
      // ShutdownWindow();

      isRunning = false;
      std::cout << "Application shutdown complete!" << std::endl;
    }

    bool IsRunning() const {
      return isRunning;
    }

    void RequestExit() {
      isRunning = false;
    }

private:
    Application() : isRunning(false), window(nullptr), inputManager(nullptr), timeManager(nullptr) {}

    // Window management 
    bool CreateWindow(int width, int height, const char* title) {
      std::cout << "Creating window..." << width << "x" << height << "-" << title << std::endl;
      // Stub: Create OS window here
      return true;
    }

    void DestroyWindow() {
      std::cout << "Destroying window..." << std::endl;
      // Stub: Cleanup window resources
    }

    void SwapBuffers() {
      // stub: present rendered frame to screen
    }

    void PollEvents() {
      // stub: process OS window messages
      // handle close, resize, etc.
    }

    // Input management
    bool InitializeInput() {
      std::cout << "Initializing input system..." << std::endl;
      return true;
    }

    void ShutdownInput() {
      std::cout << "Shutting down input system..." << std::endl;
    }

    void ProcessInput() {
      // stub: update input state for this frame
      PollEvents();
      UpdateInputState();
      
      // example: Check for escape key to exit 
      if (IsKeyPressed(27)) { // ESC key
        RequestExit();
      }
    }

    void UpdateInputState() {
      // stub: refresh input state (key presses, mouse position, etc.)
    }

    bool IsKeyPressed(int keyCode) {
      // stub: check if key is currently pressed 
      // for demo, exit after some time 
      static int frameCount = 0;
      frameCount++;
      return frameCount > 300; // Exit after ~5s 
    }

    bool IsKeyJustPressed(int keyCode) {
      // stub: check if key was pressed this frame, not last frame 
      return false;
    }

    // Time management
    bool InitializeTime() {
      std::cout << "Initializing time management..." << std::endl;
      return true;
    }

    float UpdateTime() {
      // stub: calculate delta time since last frame 
      static auto lastTime = std::chrono::high_resolution_clock::now();
      auto currentTime = std::chrono::high_resolution_clock::now();
      auto deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
      lastTime = currentTime;

      return deltaTime;
    }
    
    float GetTotalTime() {
      // stub: return time since application started 
      return 0.0f;
    }

    // Game logic 
    void Update(float deltaTime) {
      // stub: update game logic 
      static int updateCount = 0;
      updateCount++;
      if (updateCount % 60 == 0) { // Every second at 60 FPS
        std::cout << "Update tick: " << updateCount / 60 << "s (dt=" << deltaTime << ")" << std::endl;
      }
    }

    void Render() {
      // stub: Render the current frame 
      // clearn screen, draw objects, etc.
    }

    void PresentFrame() {
      // stub: present rendered frame 
      SwapBuffers();
    }
};

// Static member definition
Application* Application::instance = nullptr;

int main() {
  std::cout << "=== Blink game engine starting ===" << std::endl;

  Application& app = Application::GetInstance();

  if(!app.Initialize()) {
    std::cout << "Failed to initialize application!" << std::endl;
    return -1;
  }

  app.Run();
  app.Shutdown();

  std::cout << "=== Blink Game Engine Finished ===" << std::endl;
  return 0;
}
