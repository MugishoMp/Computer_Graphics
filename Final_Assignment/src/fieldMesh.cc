#include "fieldMesh.h"
#include "errorChecking.h"
#include <iostream>

FieldMesh::FieldMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
    : Mesh(vertices, indices) {

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3, // x,y,z
        GL_FLOAT,
        GL_FALSE,
        sizeof(GL_FLOAT) * 6, // the stride, 
        (void*)0 // starting point
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        3, // r,g,b
        GL_FLOAT,
        GL_FALSE,
        sizeof(GL_FLOAT) * 6,
        (GLvoid*)(sizeof(GL_FLOAT) * 3)
    );

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

FieldMesh::~FieldMesh() {
    // Cleanup specific to FieldMesh
}

void FieldMesh::Bind() const {
    Mesh::Bind();
    // Additional bind operations specific to FieldMesh
}

void FieldMesh::Unbind() const {
    Mesh::Unbind();
    // Additional unbind operations specific to FieldMesh
}

void FieldMesh::Render (const State &state) const {
    Mesh::Render(state);
    Bind();
    // GL_TRIANGLES implies basicaly to sample three elements at a time
    GLCheck(glDrawElements(GL_TRIANGLES, 
                    6, 
                    GL_UNSIGNED_INT, 
                    0);)
    Unbind();
}
