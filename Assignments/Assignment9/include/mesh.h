#ifndef MESH
#define MESH

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Third-party library
#include <SDL2/SDL.h>
// Include GLAD
#include <glad/glad.h>


#include "state.h"

class Mesh {
    public:
        Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
        ~Mesh();
        void Bind() const;
        void Unbind() const;
        // ... other Mesh-related methods

    private:
        GLuint VAO, VBO, IBO;
        // ... methods for setting up Meshes
};

#endif