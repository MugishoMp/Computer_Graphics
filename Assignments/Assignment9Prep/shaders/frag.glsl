#version 410 core 

in vec3 v_color;
uniform float u_time;

out vec4 color;
uniform vec2 u_resolution;

// define (pseudo-)random noise function
float random(vec2 co) {
    return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * u_time);
}


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

void main() {
    // Normalize gl_FragCoord
    vec2 uv = gl_FragCoord.xy / u_resolution;
    // because it is a standing plane, thats why we use xy instead of xz because it is not "laying on the floor" as it were so to speak
    // float randNum = random(gl_FragCoord.xy);
    // color = vec4(vec3(randNum), 1.0);

    // we are basically executing the worley function for a point that is far up, but because we are using time
    // we can manipuilate the current xy coordinate to "simulate" a coordinate that is not actually here,
    // but maybe far above the actual coordinates and map it to where we are now, kinda hard to explain.
    color = vec4(worley2((uv * 2) + (u_time * vec2(0.0, 0.001))));
}
