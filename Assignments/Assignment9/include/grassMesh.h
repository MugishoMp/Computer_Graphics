#ifndef GRASS_MESH_H
#define GRASS_MESH_H

#include "mesh.h"

class GrassMesh : public Mesh {
public:
    GrassMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~GrassMesh() override;
    void Bind() const override;
    void Unbind() const override;
    void Render() const override;

    // Additional methods specific to GrassMesh
    void ApplyWindEffect(float windStrength);

private:
    // Additional properties and methods specific to grass rendering
};

#endif // GRASS_MESH_H
