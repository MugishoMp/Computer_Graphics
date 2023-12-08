#include "mesh.h"
#include "errorChecking.h"

Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) {
    // Generate and bind the Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind the Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    // Generate and bind the Index Buffer Object
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Set up vertex attributes (position, color, etc.)
    // This depends on your vertex layout
    // Example: glVertexAttribPointer(...);

    // Unbind VAO (and optionally other buffers) to prevent unintended modifications.
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    // Clean up resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}

void Mesh::Bind() const {
    GLCheck(glBindVertexArray(VAO);)
    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, VBO);)
}

void Mesh::Unbind() const {
    glBindVertexArray(0);
    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0);)
}

void Mesh::Render() const {
}
