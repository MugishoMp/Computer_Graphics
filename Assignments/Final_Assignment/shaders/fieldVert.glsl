#version 410 core 

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;        // Added view matrix uniform
uniform mat4 u_perspective_matrix;

out vec3 v_color;

void main() {
    v_color = color;

    // Apply model, view, and perspective transformations in order
    vec4 worldPosition = u_model_matrix * vec4(position, 1.0f);
    vec4 viewPosition = u_view_matrix * worldPosition;
    vec4 clipPosition = u_perspective_matrix * viewPosition;

    gl_Position = clipPosition;
}