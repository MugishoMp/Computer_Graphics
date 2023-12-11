#ifndef GLOBAL_VARIABLES
#define GLOBAL_VARIABLES

#include <vector>

const float fieldMinX = -1.0f;
const float fieldMaxX = 1.0f;
const float fieldMinZ = -1.0f;
const float fieldMaxZ = 1.0f;

const float bladeMinWidthScale = 0.15f;
const float bladeMaxWidthScale = 0.25f;
const float bladeMinHeightScale = 0.035f;
const float bladeMaxHeightScale = 0.045f;

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
    fieldMinX, 0.0f, fieldMinZ,   1.0f, 1.0f, 0.0f, // Bottom Left
    fieldMaxX, 0.0f, fieldMinZ,   1.0f, 1.0f, 0.0f, // Bottom Right
    fieldMaxX, 0.0f, fieldMaxZ,   1.0f, 1.0f, 0.0f, // Top Right
    fieldMinX, 0.0f, fieldMaxZ,   1.0f, 1.0f, 0.0f, // Top Left
};

const std::vector<GLuint> fieldMeshIndices = {
    0, 1, 2, // First Triangle
    2, 3, 0  // Second Triangle
};

// int MAX_INSTANCES = 10000;

#endif // GLOBAL_VARIABLES
