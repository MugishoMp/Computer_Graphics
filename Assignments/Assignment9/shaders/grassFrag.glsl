#version 410 core 

in vec3 v_color;
in vec2 v_texCoord;

out vec4 color;

void main() {
    color = vec4(v_color.r, v_color.g, v_color.b, 1.0f);
}