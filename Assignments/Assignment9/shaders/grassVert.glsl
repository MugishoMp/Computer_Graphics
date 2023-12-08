#version 410 core 

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;
layout(location=2) in vec2 texCoord;

uniform mat4 u_model_matrix;
uniform mat4 u_perspective_matrix;

out vec3 v_color;
out vec2 v_texCoord;

void main() {
    v_color = color;
    v_texCoord = texCoord;

    vec4 newPosition = u_perspective_matrix * u_model_matrix * vec4(position,1.0f);

    gl_Position = vec4(newPosition.x, newPosition.y, newPosition.z, newPosition.w);
}