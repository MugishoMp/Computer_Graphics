#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glad/glad.h>

#include "state.h"

class Mesh {
public:
    Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
    virtual ~Mesh();
    virtual void Render(const State &state) const;

protected:
    virtual void Bind() const;
    virtual void Unbind() const;
    GLuint VAO, VBO, IBO, indexCount;
};

#endif // MESH_H
