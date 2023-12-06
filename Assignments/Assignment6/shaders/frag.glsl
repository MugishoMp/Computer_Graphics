#version 410 core 

in vec3 v_color;
out vec4 color;

uniform float u_offset_x; // uniform variable
uniform float u_offset_y; // uniform variable

void main() {
    color = vec4(v_color.r + u_offset_x, v_color.g + u_offset_y, v_color.b, 1.0f);
    // color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}