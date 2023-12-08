#ifndef FIELD_MESH_H
#define FIELD_MESH_H

#include "mesh.h"

class FieldMesh : public Mesh {
public:
    FieldMesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    ~FieldMesh() override;
    void Bind() const override;
    void Unbind() const override;
    void Render() const override;

    // Additional methods specific to FieldMesh

private:
    // Additional properties and methods specific to grass rendering
};

#endif // FIELD_MESH_H
