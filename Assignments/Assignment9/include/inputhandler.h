#ifndef H_INPUT_HANDLER
#define H_INPUT_HANDLER


#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Third-party library
#include <SDL2/SDL.h>
// Include GLAD
#include <glad/glad.h>

#include "state.h"

class InputHandler {
    public:
        InputHandler();
        ~InputHandler();
        void Update(State &state);
        // ... methods to get input status

    private:
        float lastX;
        float lastY;
        bool isDragging;
        // // for mouse dragging
        // float lastX = 400; // 
        // bool isDragging = false;
        // ... input-related properties
};

#endif