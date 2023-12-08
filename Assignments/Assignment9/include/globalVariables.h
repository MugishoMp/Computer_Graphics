#ifndef GLOBAL_VARIABLES
#define GLOBAL_VARIABLES

#include <vector>

// grass mesh
const std::vector<GLfloat> grassMeshVertices {
    // Positions            // Colors             // UVs
    -0.5f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,    0.0f, 0.0f, // Bottom Left (vertex 0)
     0.5f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f,    0.0f, 0.0f, // Bottom Right (vertex 1)
     0.0f, 1.0f, 0.0f,     0.0f, 1.0f, 0.0f,    1.0f, 1.0f, // Top Left (vertex 2)
};


const std::vector<GLuint> grassMeshIndices {
    0, 1, 2,  // First triangle (bottom left, bottom right, top left)
};

const std::vector<GLfloat> fieldMeshVertices = {
    // Positions          // Colors
    -1.0f, 0.0f, -1.0f,   1.0f, 1.0f, 0.0f, // Bottom Left
     1.0f, 0.0f, -1.0f,   1.0f, 1.0f, 0.0f, // Bottom Right
     1.0f, 0.0f,  1.0f,   1.0f, 1.0f, 0.0f, // Top Right
    -1.0f, 0.0f,  1.0f,   1.0f, 1.0f, 0.0f, // Top Left
};

const std::vector<GLuint> fieldMeshIndices = {
    0, 1, 2, // First Triangle
    2, 3, 0  // Second Triangle
};

#endif // GLOBAL_VARIABLES
