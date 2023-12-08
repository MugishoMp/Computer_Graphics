#include "application.h"
#include "grassMesh.h"
#include "fieldMesh.h"
#include "globalVariables.h"
#include "errorChecking.h"
// #include <glm/gtc/matrix_transform.hpp>

Application::Application() {
    // initialize program
    window = std::make_unique<Window>(state.width, state.height, "OpenGL Window");
    // state = 

    // vertex specification
    meshes.push_back(std::make_unique<FieldMesh>(fieldMeshVertices, fieldMeshIndices));
    meshes.push_back(std::make_unique<GrassMesh>(grassMeshVertices, grassMeshIndices));

    // create graphics pipeline

    // Setup input handler
    inputHandler = std::make_unique<InputHandler>();
}

void Application::Run() {

    // TEMPORARY
    std::unique_ptr<Shader> grassShader = std::make_unique<Shader>("./shaders/grassVert.glsl", "./shaders/grassFrag.glsl");
    std::unique_ptr<Shader> fieldShader = std::make_unique<Shader>("./shaders/fieldVert.glsl", "./shaders/fieldFrag.glsl");

    // TEMPORARY


    while (!this->state.quit) {
        // Handle input
        inputHandler->Update(this->state);

        // // PreRender
        renderer->PreRender(this->state);

        // Render
        for (const auto& mesh : meshes) {
            if (auto grassMesh = dynamic_cast<GrassMesh*>(mesh.get())) {
                // Render grass mesh
                renderer->Render(*grassMesh, *grassShader, this->state);
            } else if (auto fieldMesh = dynamic_cast<FieldMesh*>(mesh.get())) {
                // Render box mesh
                renderer->Render(*fieldMesh, *fieldShader, this->state);
            }
        }

        // Swap the window buffers
        window->SwapBuffers();
    }
}

void Application::Cleanup() {
    // Cleanup resources
    // The unique_ptr will automatically deallocate memory
}

Application::~Application() {
    Cleanup();
}
