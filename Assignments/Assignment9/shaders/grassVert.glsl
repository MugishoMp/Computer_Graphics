#version 410 core 

layout(location=0) in vec3 position;
layout(location=1) in vec3 color;
layout(location=2) in vec2 texCoord;

// Per-instance attributes
layout(location = 3) in vec3 instancePosition; // Instance position
layout(location = 4) in float instanceRotation; // Instance rotation (around Y-axis)
layout(location = 5) in vec2 instanceScale; // Instance rotation (around Y-axis)
layout(location = 6) in float sway_pitch; // Instance rotation (around Y-axis)
layout(location = 7) in float sway_yaw; // Instance rotation (around Y-axis)

uniform mat4 u_model_matrix;
uniform mat4 u_view_matrix;        // Added view matrix uniform
uniform mat4 u_perspective_matrix;

uniform float u_time;

out vec3 v_color;
out vec2 v_texCoord;

float wind;
float wind_scale = 1.0;
float wind_speed = 5.0;
vec3 wind_direction = vec3(0.0,0.0,-1.0);

float time = u_time * wind_speed * 0.0001;

const vec3 UP = vec3(0,1,0);
const vec3 RIGHT = vec3(0,0,1);



// define worley noise function
vec2 random2(vec2 p) {
    return fract(sin(vec2(
        dot(p, vec2(127.32, 231.4)),
        dot(p, vec2(12.3, 146.3))

    )) * 231.23);
}

float worley2(vec2 p) {
    float dist = 1.0;

    vec2 i_p = floor(p);
    vec2 f_p = fract(p);
    for(int y = -1; y <= 1; y++) {
        for(int x = -1; x <= 1; x++) {
            vec2 n = vec2(float(x), float(y));
            vec2 diff = n + random2(i_p + n) - f_p;
            dist = min(dist, length(diff));
        }
    }
    return dist;

}

// rodriguez rotation formula a formula that gives us a rotation 
// matrix that rotates a certain angle around a give axis
mat3 rodriguez(float angle, vec3 axis) {
	float s = sin(angle);
	float c = cos(angle);
	float t = 1.0 - c;
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	return mat3(
		vec3(t*x*x+c,    t*x*y-s*z,  t*x*z+s*y),
		vec3(t*x*y+s*z,  t*y*y+c,    t*y*z-s*x),
		vec3(t*x*z-s*y,  t*y*z+s*z,  t*z*z+c)
	);
}

void main() {


    // Apply rotation to the position
    float cosRot = cos(instanceRotation);
    float sinRot = sin(instanceRotation);
    vec3 rotatedPos = position;
    rotatedPos.x = position.x * cosRot - position.z * sinRot;
    rotatedPos.z = position.x * sinRot + position.z * cosRot;

    // Apply instance scale
    vec3 instanceScale = vec3(instanceScale.y, instanceScale.x, instanceScale.y);
    vec3 vertex = rotatedPos * instanceScale;


    

    
    // swaying is like the movement of the head
    float rad_sway_pitch = radians(sway_pitch); // nod yes
    float rad_sway_yaw = radians(sway_yaw); // shake no

    // vertex = rodriguez(u_time * 0.0005, UP) * vertex;




    // uv
    vec2 uv = instancePosition.xz * wind_scale;
    vec3 wind_direction_normalized = normalize(wind_direction);
    uv += wind_direction_normalized.xz * time;
    // we do times uv2 because the wind has  more effect on top
    wind = pow(worley2(uv),1) * texCoord.y;



    mat3 to_model = mat3(u_model_matrix);
    vec3 wind_forward = to_model * wind_direction_normalized * -1;
    vec3 wind_right = normalize(cross(wind_forward, UP));

    float sway_pitch_fin = rad_sway_pitch * wind;
    float sway_yaw_fin = rad_sway_yaw * sin(time) * wind;

    mat3 rotation_right = rodriguez(sway_pitch_fin, wind_right);
    mat3 rotation_forward = rodriguez(sway_yaw_fin, wind_forward);
    
    vertex = rotation_right * rotation_forward * vertex;

    // Apply model transformation
    vec4 worldPosition = u_model_matrix  * vec4(vertex, 1.0) + vec4(instancePosition, 0.0);

    // Apply view transformation
    vec4 viewPosition = u_view_matrix * worldPosition;

    // Apply perspective transformation
    gl_Position = u_perspective_matrix * viewPosition;

    // v_color = color;
    v_color = vec3(wind);
    v_texCoord = texCoord;
}
