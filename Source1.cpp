#include <SDL3/SDL.h>
#include <iostream>
#include <memory>

/**
 * Custom deleter for SDL_Window to facilitate RAII with std::unique_ptr.
 */

struct SDLWindowDeleter {
    void operator()(SDL_Window* window) const {
        if (window) {
            SDL_DestroyWindow(window);
            std::cout << "SDL_Window destroyed successfully.\n";
        }
    }
};

class GameApplication {
public:
    GameApplication(const char* title, int width, int height) {
        // 1. Initialize SDL Video Subsystem
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            throw std::runtime_error(std::string("SDL_Init Failed: ") + SDL_GetError());
        }

        // 2. Create the window with Vulkan support enabled (future-proofing)
        m_window.reset(SDL_CreateWindow(
            title,
            width,
            height,
            SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE
        ));

        if (!m_window) {
            throw std::runtime_error(std::string("Window Creation Failed: ") + SDL_GetError());
        }
    }

    ~GameApplication() {
        // SDL_Quit should be called after all SDL resources are freed
        SDL_Quit();
        std::cout << "SDL Subsystems shut down.\n";
    }

    void Run() {
        bool isRunning = true;
        SDL_Event event;

        std::cout << "Engine Loop Started.\n";

        while (isRunning) {
            // 3. Poll for OS events (Input, Close, Resize)
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    isRunning = false;
                }
            }

            // 4. Update and Render Logic will go here
            Update();
            Render();
        }
    }

private:
    std::unique_ptr<SDL_Window, SDLWindowDeleter> m_window;

    void Update() {
        // Physics and Logic updates
    }

    void Render() {
        // Swap buffers or submit command buffers
    }
};

int main(int argc, char* argv[]) {
    try {
        GameApplication app("C++ 3D Engine v1.0", 1280, 720);
        app.Run();
    }
    catch (const std::exception& e) {
        std::cerr << "Critical Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}