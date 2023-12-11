#ifndef WINDOW
#define WINDOW

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Third-party library
#include <SDL2/SDL.h>
// Include GLAD
#include <glad/glad.h>

#include "state.h"

class Window {
    public:
        Window(int width, int height, const std::string& title);
        ~Window();
        SDL_Window* GetSDLWindow();
        void SwapBuffers();
        void GetOpenGLVersionInfo();
        // ... other window-related methods

    private:
        int G_HEIGHT = 480;
        int G_WIDTH = 640;
        SDL_Window * G_GRAPHICS_APPLICATION_WINDOW = nullptr;
        SDL_GLContext G_OPENGL_CONTEXT = nullptr;

        // ... other window-related properties
};

#endif