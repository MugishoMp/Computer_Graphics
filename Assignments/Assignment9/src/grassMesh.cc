#include "grassMesh.h"
#include "errorChecking.h"
#include <iostream>

GrassMesh::GrassMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
    : Mesh(vertices, indices) {

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3, // x,y,z
        GL_FLOAT,
        GL_FALSE,
        sizeof(GL_FLOAT) * 8, // the stride, 
        (void*)0 // starting point
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        3, // r,g,b
        GL_FLOAT,
        GL_FALSE,
        sizeof(GL_FLOAT) * 8,
        (GLvoid*)(sizeof(GL_FLOAT) * 3)
    );

    // UV attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2, 
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        sizeof(GLfloat) * 8, 
        (void*)(6 * sizeof(GLfloat))
    );
    


    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

GrassMesh::~GrassMesh() {
    // Cleanup specific to GrassMesh
}

void GrassMesh::Bind() const {
    Mesh::Bind();
    // Additional bind operations specific to GrassMesh
}

void GrassMesh::Unbind() const {
    Mesh::Unbind();
    // Additional unbind operations specific to GrassMesh
}

void GrassMesh::Render () const {
    Mesh::Render();
    Bind();
    // GL_TRIANGLES implies basicaly to sample three elements at a time
    GLCheck(glDrawElements(GL_TRIANGLES, 
                    3, 
                    GL_UNSIGNED_INT, 
                    0);)
    Unbind();
}

void GrassMesh::ApplyWindEffect(float windStrength) {
    // Implement wind effect logic
}