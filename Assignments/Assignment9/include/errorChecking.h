#ifndef ERROR_CHECKING_H
#define ERROR_CHECKING_H

#include <iostream>
#include <glad/glad.h> // Include GLAD

// Clears any existing OpenGL errors
void GLClearAllErrors();

// Checks for OpenGL errors and returns true if an error occurred
bool GLCheckErrorStatus(const char* function, int line);

// Macro for OpenGL error checking
#define GLCheck(x) GLClearAllErrors(); x; GLCheckErrorStatus(#x, __LINE__);

#endif // ERROR_CHECKING_H
