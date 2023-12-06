#version 410 core 

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

uniform mat4 u_model_matrix;

out vec3 v_color;

void main() {
    v_color = color;

    vec4 newPosition = u_model_matrix * vec4(position,1.0f);

    gl_Position = vec4(newPosition.x, newPosition.y, newPosition.z, 1.0f);
}