#ifndef RENDERER
#define RENDERER

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Third-party library
#include <SDL2/SDL.h>
// Include GLAD
#include <glad/glad.h>

#include "mesh.h"
#include "shader.h"

#include "state.h"

class Renderer {
    public:
        Renderer();
        ~Renderer();
        void Render(const Mesh& mesh, const Shader& shader) const;
        // ... other rendering-related methods

    private:
        // ... rendering-related properties
};

#endif