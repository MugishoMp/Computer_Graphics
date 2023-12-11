#version 410 core 

in vec3 v_color;
in vec2 v_texCoord;

out vec4 color;


void main() {

    
    // Define Ambient Light
    vec3 ambientLight = vec3(2.0, 2.0, 2.0); // Low-intensity white light
    vec3 lightColor = vec3(1.0, 1.0, 1.0); // White light
    // #0D2601
    vec4 Ambient = vec4(ambientLight,1.0) * vec4(lightColor, 1.0);
    // color = vec4(v_color.r, v_color.g, v_color.b, 1.0f);

    // #467302
    vec4 color_bottom = vec4(0.051, 0.149, 0.004,1) ;
    // #0D2601
    vec4 color_top = vec4(0.275, 0.451, 0.008,1);
    
    color = vec4(v_color.r, v_color.g, v_color.b, 1.0f);
}