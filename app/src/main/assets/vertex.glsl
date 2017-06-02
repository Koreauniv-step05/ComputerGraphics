#version 300 es

uniform mat4 worldMat, viewMat, projMat; // transformation matrix
uniform vec3 eyePos, lightPosL, lightPosR; // camera position, light positions
uniform float lightAttL[3], lightAttR[3]; // light attenuations

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 v_normal;
out vec2 v_texCoord;
out vec3 v_view, v_lightL, v_lightR;
out float v_attL, v_attR;

void main() {

    // clip-space position
    gl_Position = projMat * viewMat * worldMat * vec4(position, 1.0);

    // world-space vertex normal
    v_normal = normalize(transpose(inverse(mat3(worldMat))) * normal);

    // texture coordinates
    v_texCoord = texCoord;

    // world-space position
    vec3 worldPos = (worldMat * vec4(position, 1.0)).xyz;

    // view vector
    v_view = normalize(eyePos - worldPos);

    // light vectors
    v_lightL = normalize(lightPosL - worldPos);
    v_lightR = normalize(lightPosR - worldPos);

    // attenuations
    float distL = distance(worldPos, lightPosL);
    float distR = distance(worldPos, lightPosR);
    v_attL = 1.0 / (lightAttL[0] + lightAttL[1] * distL + lightAttL[2] * distL * distL);
    v_attR = 1.0 / (lightAttR[0] + lightAttR[1] * distR + lightAttR[2] * distR * distR);

}
