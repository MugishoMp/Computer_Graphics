#include "errorChecking.h"

void GLClearAllErrors() {
    while(glGetError() != GL_NO_ERROR) {

    }
}

// Returns true if we have an error
bool GLCheckErrorStatus(const char* function, int line) {
    while(GLenum error = glGetError()) {
        std::cout << "OpenGl Error: " << error 
                  << "\t Line: " << line
                  << "\t function: " << function 
                  << std::endl;
        return true;
    }
    return false;
}