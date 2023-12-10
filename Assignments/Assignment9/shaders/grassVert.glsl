#version 410 core 

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;
layout(location=2) in vec2 texCoord;

// Per-instance attributes
layout(location = 3) in vec3 instancePosition; // Instance position
layout(location = 4) in float instanceRotation; // Instance rotation (around Y-axis)
layout(location = 5) in vec2 instanceScale; // Instance rotation (around Y-axis)

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;        // Added view matrix uniform
uniform mat4 u_perspective_matrix;

out vec3 v_color;
out vec2 v_texCoord;

void main() {
    v_color = color;
    v_texCoord = texCoord;

    // Apply rotation to the position
    float cosRot = cos(instanceRotation);
    float sinRot = sin(instanceRotation);
    vec3 rotatedPos = position;
    rotatedPos.x = position.x * cosRot - position.z * sinRot;
    rotatedPos.z = position.x * sinRot + position.z * cosRot;


    // Apply instance scale
    vec3 instanceScale = vec3(instanceScale.y, instanceScale.x, instanceScale.y);
    vec3 scaledPosition = rotatedPos * instanceScale;

    // Apply model transformation
    vec4 worldPosition = u_model_matrix * vec4(scaledPosition, 1.0) + vec4(instancePosition, 0.0);

    // Apply view transformation
    vec4 viewPosition = u_view_matrix * worldPosition;

    // Apply perspective transformation
    gl_Position = u_perspective_matrix * viewPosition;
}
