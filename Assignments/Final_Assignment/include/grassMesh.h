#ifndef GRASS_MESH_H
#define GRASS_MESH_H

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "mesh.h"
#include "state.h"

struct InstanceData {
    glm::vec3 position;
    float rotation;
    glm::vec2 scale;
    float sway_pitch = 80.0f;
    float sway_yaw = 45.0f;
};

class GrassMesh : public Mesh {
public:
    GrassMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~GrassMesh() override;
    void Bind() const override;
    void Unbind() const override;
    void Render(const State &state) const override;

    // Additional methods specific to GrassMesh
    void UpdateInstances(const std::vector<InstanceData>& newInstances);
    void InstanceRender(const State &state) const;
    void updateInstanceOrder(const State &state);
    void ApplyWindEffect(float windStrength);


private:
    GLuint instanceVBO; // Buffer for instance data
    std::vector<InstanceData> instances;
    // Additional properties and methods specific to grass rendering
};

#endif // GRASS_MESH_H
