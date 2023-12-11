#include "inputhandler.h"
#include "errorChecking.h"


InputHandler::InputHandler() : lastX(0.0f), lastY(0.0f), isDragging(false) {
    // Initialization code
}


InputHandler::~InputHandler() {
    // nothing to do
}

void InputHandler::Update(State &state) {
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            std::cout << "Goodbye!" << std::endl;
            state.quit = true;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN) {
            if (e.button.button == SDL_BUTTON_LEFT) { // Left mouse button
                isDragging = true;
                lastX = e.motion.x;
                lastY = e.motion.y;
            }
        }
        else if (e.type == SDL_MOUSEBUTTONUP) {
            if (e.button.button == SDL_BUTTON_LEFT) {
                isDragging = false;
            }
        }
        else if (e.type == SDL_MOUSEMOTION) {
            if (isDragging) {
                float xoffset = e.motion.x - lastX;
                lastX = e.motion.x;

                float yoffset = e.motion.y - lastY;
                lastY = e.motion.y;

                // Adjust sensitivity as needed
                const float sensitivity = 0.1f;
                xoffset *= sensitivity;
                yoffset *= sensitivity;

                state.rotate -= xoffset;
                state.offsetY += yoffset;
                std::cout << "rotation: " << state.rotate << std::endl;
            }
        }
    }

    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    if (keyboardState[SDL_SCANCODE_Q]) {
        std::cout << "Goodbye!" << std::endl;
        state.quit = true;
    }
    if (keyboardState[SDL_SCANCODE_RIGHT]) {
        state.rotate += 0.05f;
        std::cout << "rotation: " << state.rotate << std::endl;
    }
    if (keyboardState[SDL_SCANCODE_LEFT]) {
        state.rotate -= 0.05f;
        std::cout << "rotation: " << state.rotate << std::endl;
    }
    if (keyboardState[SDL_SCANCODE_UP]) {
        state.offsetZ += 0.001f;
        std::cout << "offset z: " << state.offsetZ << std::endl;
    }
    if (keyboardState[SDL_SCANCODE_DOWN]) {
        state.offsetZ -= 0.001f;
        std::cout << "offset z: " << state.offsetZ << std::endl;
    }
}