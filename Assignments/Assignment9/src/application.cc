#include "application.h"

Application::Application() {
    // Initialize SDL and create a window
    window = std::make_unique<Window>(640, 480, "OpenGL Window");
    renderer = std::make_unique<Renderer>();
    
    // grass mesh

    const std::vector<GLfloat> vertices {
        // 0 - vertex
        -0.5f, -0.5f, 0.0f, // left vertex 1 position
        1.0f, 0.0f, 0.0f, // vertex 1 color
        // 1 - vertex
        0.5f,  -0.5f, 0.0f, // right vertex 2 position
        0.0f, 1.0f, 0.0f, // vertex 2 color
        // 2 - vertex
        -0.5f,   0.5f, 0.0f, // top vertex 3 position
        0.0f, 0.0f, 1.0f, // vertex 3 color
        // 3 - vertex
        0.5f, 0.5f, 0.0f, // top right vertex 1 position
        1.0f, 0.0f, 0.0f, // vertex 1 color

    };
    const std::vector<GLuint> indices {
        // triangle 1
        2,0,1,
        // triangle 2
        3,2,1
    };
    meshes.push_back(std::make_unique<Mesh>(vertices, indices)); // Mesh 1
    // box mesh

    // // Initialize the renderer
    // renderer = std::make_unique<Renderer>();

    // Load shaders
    shader = std::make_unique<Shader>("shaders/vert.glsl", "shaders/frag.glsl");

    // // Create a buffer for rendering
    // buffer = std::make_unique<Buffer>();

    // Setup input handler
    inputHandler = std::make_unique<InputHandler>();
}

void Application::Run() {
    while (!this->state.quit) {
        // std::cout << "test" << std::endl;
        // Handle input
        inputHandler->Update(this->state);

        // // Update the application state

        // // Prepare for rendering
        // renderer->PreDraw(this->state);

        for (const auto& mesh : meshes) {
            renderer->Render(*mesh, this->shader);
        }
        // // Render using the shader and buffer
        // renderer->Draw(this->state);

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
