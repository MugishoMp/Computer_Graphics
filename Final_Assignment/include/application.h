#ifndef H_APPLICATION
#define H_APPLICATION

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Third-party library
#include <SDL2/SDL.h>
// Include GLAD
#include <glad/glad.h>

#include "state.h"
#include "window.h"
#include "mesh.h"
#include "renderer.h"
#include "inputhandler.h"

class Application {
public:
    Application();
    ~Application();
    void Run();
    void Cleanup();
    // ... other application-related methods

private:
    State state;
    std::unique_ptr<Window> window;
    std::vector<std::unique_ptr<Mesh>> meshes;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<InputHandler> inputHandler;
    // ... other application-related properties
};

#endif