#include "material.h"

Material::Material(Program* program, Texture* texture)
        : specular(1.0f),
          ambient(0.6f),
          emissive(0.0f),
          shininess(5.0f) {

    // create
    create(program, texture);

    // update
    update();
}

void Material::create(Program* program, Texture* texture) {
    LOG_PRINT_DEBUG("Create material");

    // set attributes
    this->program = program;
    this->texture = texture;

    // check uniform locations
    if (glGetUniformLocation(program->id, "matSpec") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "matSpec");
    }
    if (glGetUniformLocation(program->id, "matAmbi") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "matAmbi");
    }
    if (glGetUniformLocation(program->id, "matEmit") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "matEmit");
    }
    if (glGetUniformLocation(program->id, "matSh") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "matSh");
    }
}

void Material::update() const {
//    LOG_PRINT_DEBUG("Update material");

    // update texture
    if (texture) texture->update();

    // get uniform locations
    GLint matSpecLoc = glGetUniformLocation(program->id, "matSpec");
    GLint matAmbiLoc = glGetUniformLocation(program->id, "matAmbi");
    GLint matEmitLoc = glGetUniformLocation(program->id, "matEmit");
    GLint matShLoc = glGetUniformLocation(program->id, "matSh");

    // set uniform data
    if (matSpecLoc >= 0) glUniform3fv(matSpecLoc, 1, value_ptr(specular));
    if (matAmbiLoc >= 0) glUniform3fv(matAmbiLoc, 1, value_ptr(ambient));
    if (matEmitLoc >= 0) glUniform3fv(matEmitLoc, 1, value_ptr(emissive));
    if (matShLoc >= 0) glUniform1f(matShLoc, shininess);
}
