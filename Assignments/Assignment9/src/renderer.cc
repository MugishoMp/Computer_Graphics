#include "renderer.h"
#include "errorChecking.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::PreRender(const State& state) const {
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0,0,state.width, state.height);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Renderer::Render(const Mesh& mesh, const Shader& shader, const State &state) const {
    shader.Bind();
    // TEMPORARY
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, state.offsetZ));
    model           = glm::rotate(model, glm::radians(state.rotate), glm::vec3(0.0f,1.0f,0.0f));
    model           = glm::scale(model, glm::vec3(1.0f,1.0f,1.0f));
    glm::mat4 perspective = glm::perspective(glm::radians(45.0f), 
    (float)state.width / (float)state.height,
    0.1f,
    10.0f);
    // TEMPORARY

    shader.SetUniform("u_model_matrix", model);
    shader.SetUniform("u_perspective_matrix", perspective);
    // Set other uniforms as needed

    mesh.Render();

    shader.Unbind();
}
