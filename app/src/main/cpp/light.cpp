#include "light.h"

Light::Light(Program* program)
        : position(0.0f),
          attenuation{0.005f, 0.01f, 0.015f},
          diffuse(0.8f),
          specular(1.0f),
          ambient(0.05f) {

    // create
    create(program);

    // update
    update();
}

void Light::create(Program* program) {
    LOG_PRINT_DEBUG("Create light");

    // set attribute
    this->program = program;
}

void Light::update() const {
//    LOG_PRINT_DEBUG("Update light");
}

LeftLight::LeftLight(Program *program)
        : Light(program) {

}

void LeftLight::create(Program *program) {
    // call super class method
    Light::create(program);

    // check uniform locations
    if (glGetUniformLocation(program->id, "srcDiffL") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "srcDiffL");
    }
    if (glGetUniformLocation(program->id, "srcSpecL") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "srcSpecL");
    }
    if (glGetUniformLocation(program->id, "srcAmbiL") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "srcAmbiL");
    }
    if (glGetUniformLocation(program->id, "lightPosL") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "lightPosL");
    }
    if (glGetUniformLocation(program->id, "lightAttL") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "lightAttL");
    }
}

void LeftLight::update() const {
    // call super class method
    Light::update();

    // get uniform locations
    GLint srcDiffLoc = glGetUniformLocation(program->id, "srcDiffL");
    GLint srcSpecLoc = glGetUniformLocation(program->id, "srcSpecL");
    GLint srcAmbiLoc = glGetUniformLocation(program->id, "srcAmbiL");
    GLint lightPosLoc = glGetUniformLocation(program->id, "lightPosL");
    GLint lightAttLoc = glGetUniformLocation(program->id, "lightAttL");

    // set uniform data
    if (srcDiffLoc >= 0) glUniform3fv(srcDiffLoc, 1, value_ptr(diffuse));
    if (srcSpecLoc >= 0) glUniform3fv(srcSpecLoc, 1, value_ptr(specular));
    if (srcAmbiLoc >= 0) glUniform3fv(srcAmbiLoc, 1, value_ptr(ambient));
    if (lightPosLoc >= 0) glUniform3fv(lightPosLoc, 1, value_ptr(position));
    if (lightAttLoc >= 0) glUniform1fv(lightAttLoc, 3, attenuation);
}

RightLight::RightLight(Program *program)
        : Light(program) {

}

void RightLight::create(Program *program) {
    // call super class method
    Light::create(program);

    // check uniform locations
    if (glGetUniformLocation(program->id, "srcDiffR") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "srcDiffR");
    }
    if (glGetUniformLocation(program->id, "srcSpecR") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "srcSpecR");
    }
    if (glGetUniformLocation(program->id, "srcAmbiR") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "srcAmbiR");
    }
    if (glGetUniformLocation(program->id, "lightPosR") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "lightPosR");
    }
    if (glGetUniformLocation(program->id, "lightAttR") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "lightAttR");
    }
}

void RightLight::update() const {
    // call super class method
    Light::update();

    // get uniform locations
    GLint srcDiffLoc = glGetUniformLocation(program->id, "srcDiffR");
    GLint srcSpecLoc = glGetUniformLocation(program->id, "srcSpecR");
    GLint srcAmbiLoc = glGetUniformLocation(program->id, "srcAmbiR");
    GLint lightPosLoc = glGetUniformLocation(program->id, "lightPosR");
    GLint lightAttLoc = glGetUniformLocation(program->id, "lightAttR");

    // set uniform data
    if (srcDiffLoc >= 0) glUniform3fv(srcDiffLoc, 1, value_ptr(diffuse));
    if (srcSpecLoc >= 0) glUniform3fv(srcSpecLoc, 1, value_ptr(specular));
    if (srcAmbiLoc >= 0) glUniform3fv(srcAmbiLoc, 1, value_ptr(ambient));
    if (lightPosLoc >= 0) glUniform3fv(lightPosLoc, 1, value_ptr(position));
    if (lightAttLoc >= 0) glUniform1fv(lightAttLoc, 3, attenuation);
}
