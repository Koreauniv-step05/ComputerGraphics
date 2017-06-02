#include "texture.h"

Texture::Texture(Program *program, const vector<Texel> &texels, const GLsizei size) {

    // create
    create(program);

    // set data
    data(texels, size);

    // update
    update();
}

Texture::~Texture() {

    // destroy
    destroy();
}

void Texture::create(Program *program) {
    LOG_PRINT_DEBUG("Create texture");

    // set attribute
    this->program = program;

    // generate
    glGenTextures(1, &id);

    // check id
    if (!id) {
        LOG_PRINT_ERROR("Fail to generate texture");
    }

    // check uniform location
    if (glGetUniformLocation(program->id, "s_tex0") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "s_tex0");
    }
}

void Texture::data(const vector<Texel> &texels, const GLsizei size) {
    LOG_PRINT_DEBUG("Set texture data");

    // bind
    glBindTexture(GL_TEXTURE_2D, id);

    // set data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size, size,
                 0, GL_RGB, GL_UNSIGNED_BYTE, texels.data());

    // generate mipmap
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::update() const {
//    LOG_PRINT_DEBUG("Update texture");

    // get uniform location
    GLint s_tex0Loc = glGetUniformLocation(program->id, "s_tex0");

    // active and bind
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);

    // set parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // set uniform data
    if (s_tex0Loc >= 0) glUniform1i(s_tex0Loc, 0);
}

void Texture::destroy() {
    LOG_PRINT_DEBUG("Destroy texture");

    // delete
    glDeleteTextures(1, &id);
}
