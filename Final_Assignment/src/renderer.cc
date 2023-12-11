#include "renderer.h"
#include "errorChecking.h"

Renderer::Renderer() {

}

Renderer::~Renderer() {

}

void Renderer::PreRender(const State& state) const {
    // Make sure that depth testing is enabled. This is done using 
    // glEnable(GL_DEPTH_TEST);. Without depth testing enabled, 
    // OpenGL will draw objects in the order you issue the draw 
    // calls, ignoring their actual distance from the camera.
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0,0,state.width, state.height);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

// TEMPORARY - make a dedicated camera class
void setupCamera(const Shader& shader, State &state) {

    {
        glm::mat4 model = glm::mat4(1.0f);
        // Apply translation based on state.offsetZ
        // Assuming state.offsetZ affects the position along the Z-axis
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        // Apply rotation based on state.rotate
        // Assuming state.rotate is the rotation around the Y-axis
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // Apply scaling if necessary (here it's uniform scaling by 1.0, so it has no effect)
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        // Set the model matrix uniform 
        shader.SetUniform("u_model_matrix", model);
    }

    {
        // View matrix
        float radius = glm::length(glm::vec3(0.0f, 1.0f, state.offsetZ));
        float horizontalAngle = glm::radians(state.rotate); // Horizontal angle (rotate) in radians
        float verticalAngle = glm::radians(state.offsetY);  // Vertical angle (yOffset) in radians

        // Calculate the camera's position using spherical coordinates
        glm::vec3 cameraPosition;
        cameraPosition.x = sin(horizontalAngle) * cos(verticalAngle) * radius;
        cameraPosition.y = sin(verticalAngle) * radius;  // Adjusted for vertical rotation
        cameraPosition.z = cos(horizontalAngle) * cos(verticalAngle) * radius;

        glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);   // Camera is looking at the origin
        glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);    // 'Up' direction in world space
        glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, upDirection);
        // set camera position state variable
        state.cameraPosition = cameraPosition;
        // Set the view matrix uniform
        shader.SetUniform("u_view_matrix", view);
    }

    {
        // Perspective matrix (unchanged from your original setup)
        glm::mat4 perspective = glm::perspective(glm::radians(45.0f), (float)state.width / (float)state.height, 0.1f, 10.0f);
        // Set the perspective matrix uniform
        shader.SetUniform("u_perspective_matrix", perspective);
    }

    {

        // get the current time: the number of ticks from when sdl was initialized
        float currentTime = SDL_GetTicks();
        shader.SetUniform("u_time", currentTime);
    }


    // return cameraPosition;
}

void Renderer::Render(const Mesh& mesh, const Shader& shader, State &state) const {
    shader.Bind();

    setupCamera(shader, state);

    mesh.Render(state);

    shader.Unbind();
}
