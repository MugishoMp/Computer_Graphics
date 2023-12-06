#version 410 core 

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;

uniform float u_offset_x; // uniform variable
uniform float u_offset_y; // uniform variable

out vec3 v_color;

void main() {
    v_color = color;
    gl_Position = vec4(position.x + u_offset_x, position.y + u_offset_y, position.z, 1.0f);
}