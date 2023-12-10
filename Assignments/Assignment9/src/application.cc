#include "application.h"
#include "grassMesh.h"
#include "fieldMesh.h"
#include "globalVariables.h"
#include "errorChecking.h"
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
// #include <glm/gtc/matrix_transform.hpp>



glm::vec3 generateRandomPositionXZ(float minX, float maxX, float minZ, float maxZ) {
    float x = glm::linearRand(minX, maxX);
    float z = glm::linearRand(minZ, maxZ);

    return glm::vec3(x, 0.0f, z); // x is always 0
}

glm::vec2 generateRandomVec2(float minX, float maxX, float minY, float maxY) {
    float x = glm::linearRand(minX, maxX);
    float y = glm::linearRand(minY, maxY);
    return glm::vec2(x, y); // x is always 0
}

float randomRotationRadians() {
    return glm::linearRand(0.0f, glm::pi<float>());
}

Application::Application() {
    // initialize program
    window = std::make_unique<Window>(state.width, state.height, "OpenGL Window");
    // state = 

    // vertex specification
    meshes.push_back(std::make_unique<FieldMesh>(fieldMeshVertices, fieldMeshIndices));
    meshes.push_back(std::make_unique<GrassMesh>(grassMeshVertices, grassMeshIndices));


    // grass factory
    {
        Mesh* firstMesh = meshes[1].get(); // Gets the raw pointer to the second Mesh

        // If you need to specifically work with GrassMesh and are sure the first mesh is a GrassMesh
        GrassMesh* firstGrassMesh = dynamic_cast<GrassMesh*>(firstMesh);
        if (firstGrassMesh) {
            // Generate instance data
            // 10 blades of grass
            std::vector<InstanceData> grassInstances;
            for (int i = 0; i < 100; ++i) {
                InstanceData instance;
                instance.position = generateRandomPositionXZ(fieldMinX, fieldMaxX, fieldMinZ, fieldMaxZ);
                instance.scale = generateRandomVec2(bladeMinWidthScale, bladeMaxWidthScale, bladeMinHeightScale, bladeMaxHeightScale);
                instance.rotation = randomRotationRadians();
                grassInstances.push_back(instance);
            }

            // Update grass mesh with instance data
            firstGrassMesh->UpdateInstances(grassInstances);
        }
    }
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
                // grassMesh->updateInstanceOrder(this->state);
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
