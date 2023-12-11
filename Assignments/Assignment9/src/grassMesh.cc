#include "grassMesh.h"
#include "errorChecking.h"
#include "globalVariables.h"
#include <iostream>

#include <glm/glm.hpp>

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
    

    // Generate and bind instance VBO
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    // For now, just allocate buffer, data will be updated later
    glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceData) * 100, nullptr, GL_DYNAMIC_DRAW);

    // Set up instance attribute pointers
    glEnableVertexAttribArray(3); // Instance position
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)offsetof(InstanceData, position));
    glVertexAttribDivisor(3, 1); // Tell OpenGL this is an instanced vertex attribute.

    glEnableVertexAttribArray(4); // Instance rotation
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)offsetof(InstanceData, rotation));
    glVertexAttribDivisor(4, 1); // Instanced attribute

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)offsetof(InstanceData, scale));
    glVertexAttribDivisor(5, 1); // Instanced attribute

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)offsetof(InstanceData, sway_pitch));
    glVertexAttribDivisor(6, 1); // Instanced attribute

    glEnableVertexAttribArray(7);
    glVertexAttribPointer(7, 1, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)offsetof(InstanceData, sway_yaw));
    glVertexAttribDivisor(7, 1); // Instanced attribute

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
    glDisableVertexAttribArray(5);
    glDisableVertexAttribArray(6);
    glDisableVertexAttribArray(7);
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

void GrassMesh::Render (const State &state) const {
    // Mesh::Render();
    // Bind();
    // // GL_TRIANGLES implies basicaly to sample three elements at a time
    // GLCheck(glDrawElements(GL_TRIANGLES, 
    //                 3, 
    //                 GL_UNSIGNED_INT, 
    //                 0);)
    // Unbind();
    InstanceRender(state);
}

void GrassMesh::UpdateInstances(const std::vector<InstanceData>& newInstances) {
    instances = newInstances;
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceData) * instances.size(), instances.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GrassMesh::InstanceRender(const State &state) const{
    Bind();
    std::cout << "instances size: " << instances.size() << std::endl;
    // sort based on distance from the camera
    GLCheck(glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0, instances.size());)
    Unbind();
}

void sortInstancesByCameraDistance(std::vector<InstanceData>& instances, const glm::vec3& cameraPosition) {
    std::sort(instances.begin(), instances.end(), 
        [&cameraPosition](const InstanceData& a, const InstanceData& b) -> bool {
            float distA = glm::length(cameraPosition - a.position);
            float distB = glm::length(cameraPosition - b.position);
            return distA > distB;  // Sort in descending order of distance
    });
}

void GrassMesh::updateInstanceOrder(const State &state) {
    // Implement wind effect logic
    sortInstancesByCameraDistance(instances, state.cameraPosition);
}

void GrassMesh::ApplyWindEffect(float windStrength) {
    // Implement wind effect logic
}