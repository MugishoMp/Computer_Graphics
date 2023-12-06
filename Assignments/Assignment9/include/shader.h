#ifndef SHADER
#define SHADER

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

// Third-party library
#include <SDL2/SDL.h>
// Include GLAD
#include <glad/glad.h>

class Shader {
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Shader();
        void Bind() const;
        void Unbind() const;
        GLuint GetProgramID() const;
        // ... other shader-related methods

    private:
        GLuint programID;
        // ... methods for compiling and linking shaders
};

#endif