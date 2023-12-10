#include "inputhandler.h"
#include "errorChecking.h"


InputHandler::InputHandler() {
    // nothing to do
}


InputHandler::~InputHandler() {
    // nothing to do
}

void InputHandler::Update(State &state) {
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            std::cout << "Goodbye!" << std::endl;
            state.quit = true;
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