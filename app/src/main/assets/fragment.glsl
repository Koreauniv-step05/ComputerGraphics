#version 300 es

precision mediump float;

uniform sampler2D s_tex0; // texture sampler

uniform vec3 matSpec, matAmbi, matEmit; // material paramters
uniform float matSh; // material shininess
uniform vec3 srcDiffL, srcSpecL, srcAmbiL; // left light parameters
uniform vec3 srcDiffR, srcSpecR, srcAmbiR; // right light parameters

in vec3 v_normal;
in vec2 v_texCoord;
in vec3 v_view, v_lightL, v_lightR;
in float v_attL, v_attR;

layout(location = 0) out vec4 fragColor;

void main() {

    // re-normalize unit vectors (normal, view, and light vectors)
    vec3 normal = normalize(v_normal);
    vec3 view = normalize(v_view);
    vec3 lightL = normalize(v_lightL);
    vec3 lightR = normalize(v_lightR);

    // diffuse term
    vec3 matDiff = texture(s_tex0, v_texCoord).rgb;
    vec3 diffL = max(dot(normal, lightL), 0.0) * srcDiffL * matDiff;
    vec3 diffR = max(dot(normal, lightR), 0.0) * srcDiffR * matDiff;
    vec3 diff = v_attL * diffL + v_attR * diffR;

    // specular term
    vec3 reflL = 2.0 * normal * dot(normal, lightL) - lightL;
    vec3 reflR = 2.0 * normal * dot(normal, lightR) - lightR;
    vec3 specL = pow(max(dot(reflL, view), 0.0), matSh) * srcSpecL * matSpec;
    vec3 specR = pow(max(dot(reflR, view), 0.0), matSh) * srcSpecR * matSpec;
    vec3 spec = v_attL * specL + v_attR * specR;

    // ambient term
    vec3 ambiL = srcAmbiL * matAmbi;
    vec3 ambiR = srcAmbiR * matAmbi;
    vec3 ambi = ambiL + ambiR;

    // final output color with alpha value 1.0
    fragColor = vec4(diff + spec + ambi + matEmit, 1.0);

}
