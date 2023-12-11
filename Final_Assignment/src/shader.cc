#include "shader.h"
#include "errorChecking.h"

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    std::string vertexShaderSource      = LoadShaderSource(vertexShaderPath);
    std::string fragmentShaderSource    = LoadShaderSource(fragmentShaderPath);

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    LinkProgram(vertexShader, fragmentShader);
}
Shader::~Shader() {

}
void Shader::Bind() const {
    glUseProgram(programID);
}
void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::SetUniform(const std::string& name, int value) const {
    GLuint location = glGetUniformLocation(programID, name.c_str());
    if (location >= 0) {
        glUniform1i(location, value);
    } else {
        std::cout << "Could nt find location value int" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Shader::SetUniform(const std::string& name, float value) const {
    GLuint location = glGetUniformLocation(programID, name.c_str());
    if (location >= 0) {
        glUniform1f(location, value);
    } else {
        std::cout << "Could nt find location value float" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Shader::SetUniform(const std::string& name, const glm::mat3& mat) const {
    GLuint location = glGetUniformLocation(programID, name.c_str());
    if (location >= 0) {
        glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
    } else {
        std::cout << "Could nt find location matrix 3" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Shader::SetUniform(const std::string& name, const glm::mat4& mat) const {
    GLuint location = glGetUniformLocation(programID, name.c_str());
    if (location >= 0) {
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    } else {
        std::cout << "Could nt find location matrix 4" << std::endl;
        exit(EXIT_FAILURE);
    }
}

GLuint Shader::GetProgramID() const {
    return this->programID;
}

GLuint Shader::CompileShader(GLenum type, const std::string& source) {
    GLuint shaderObject;

    // create the shader
    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    } else if (type == GL_FRAGMENT_SHADER) {
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    }

    // setup the source code
    const char * src = source.c_str();
    glShaderSource(shaderObject, 1, &src, nullptr);
    // compile it
    glCompileShader(shaderObject);

    // return the shader object
    return shaderObject;
}

void Shader::LinkProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint programObject = glCreateProgram();
    // we are basically adding all the components of the pipeline together
    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    glLinkProgram(programObject);

    // validate our program (pipeline)
    glValidateProgram(programObject);
    //glDetachShader, glDeleteShader
    this->programID = programObject;
}

std::string Shader::LoadShaderSource(const std::string& filepath) {
    // resulting shader program as string
    std::string result = "";

    std::string line = "";

    std::ifstream shaderFile(filepath.c_str());

    if(shaderFile.is_open()) {
        while(std::getline(shaderFile, line)) {
            result += line + '\n';
        }
        shaderFile.close();
    }

    return result;
}