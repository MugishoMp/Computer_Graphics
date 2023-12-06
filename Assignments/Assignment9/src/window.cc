#include "window.h"


Window::Window(int width, int height, const std::string& title) {
    // we initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL2 Could not initialize fideo subsystem"
                  << std::endl;
        exit(1);
    }

    // we setup some attributes for the opengl version
    // Before we create our window, specify OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // context that we want to set up for opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    // created the window
    G_GRAPHICS_APPLICATION_WINDOW = SDL_CreateWindow(
        "OpenGL Window",
        0,
        0,
        G_WIDTH,
        G_HEIGHT,
        SDL_WINDOW_OPENGL);

    if (G_GRAPHICS_APPLICATION_WINDOW == nullptr) {
        std::cout << "SDL_Window was not able to be created"
                  << std::endl;
        exit(1);
    }

    // created the opengl context
    G_OPENGL_CONTEXT = SDL_GL_CreateContext(G_GRAPHICS_APPLICATION_WINDOW);

    if (G_OPENGL_CONTEXT == nullptr) {
        std::cout << "OpenGL context not available"
                  << std::endl;
        exit(1);
    }

    // we set up using the glad library a way have all of those
    // OpenGL functions available to us
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout << "glad was not initialized" << std::endl;
        exit(1);
    }

    GetOpenGLVersionInfo();
}

Window::~Window() {
    SDL_DestroyWindow(this->G_GRAPHICS_APPLICATION_WINDOW);

    SDL_Quit();
}

SDL_Window* Window::GetSDLWindow() {
    return this->G_GRAPHICS_APPLICATION_WINDOW;
}

void Window::SwapBuffers() {
    SDL_GL_SwapWindow(this->G_GRAPHICS_APPLICATION_WINDOW);
}

void Window::GetOpenGLVersionInfo() {
    // glad: header file that will setup opengl functions

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}