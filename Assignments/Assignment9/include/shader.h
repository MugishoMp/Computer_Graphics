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
// GLM
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();
        void Bind() const; // Activate the shader program
        void Unbind() const; // Activate the shader program
        void SetUniform(const std::string& name, int value) const; // Set an int uniform
        void SetUniform(const std::string& name, float value) const;
        void SetUniform(const std::string& name, const glm::mat3& value) const;
        void SetUniform(const std::string& name, const glm::mat4& value) const;
        // Consider adding more SetUniform overloads for other types (float, glm::vec3, glm::mat4, etc.)
        GLuint GetProgramID() const;

    private:
        GLuint programID;
        GLuint CompileShader(GLenum type, const std::string& source); // Returns shader ID
        void LinkProgram(GLuint vertexShader, GLuint fragmentShader);
        std::string LoadShaderSource(const std::string& filepath);
};

#endif