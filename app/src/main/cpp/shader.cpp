#include "shader.h"

Shader::Shader(GLenum type, const char* filename) {

    // create
    create(type);

    // set source
    source(filename);

    // compile
    compile();
}

Shader::~Shader() {

    // delete
    destroy();
}

void Shader::create(GLenum type) {
    LOG_PRINT_DEBUG("Create %s shader", type == GL_VERTEX_SHADER ? "vertex" : "fragment");

    // create
    id = glCreateShader(type);

    // check id
    if (!id) {
        LOG_PRINT_ERROR("Fail to create shader");
    }
}

void Shader::source(const char* filename) const {
    LOG_PRINT_DEBUG("Set shader source");

    // load source from asset
    const char* src = Asset::load(filename);
    LOG_PRINT_DEBUG("Shader source: \n%s", src);

    // check source
    if (!src) {
        LOG_PRINT_ERROR("Fail to load shader source");
        return;
    }

    // set shader source
    glShaderSource(id, 1, &src, NULL);
    delete[] src;
}

void Shader::compile() const {
    LOG_PRINT_DEBUG("Compile shader");

    // compile
    glCompileShader(id);

    // check compile status
    GLint compileStatus;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus) {

        // check information log length
        GLint infoLogLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength) {

            // print information log
            GLchar* infoLog = new GLchar[infoLogLength];
            glGetShaderInfoLog(id, infoLogLength, NULL, infoLog);
            LOG_PRINT_ERROR("Fail to compile shader: \n%s", infoLog);
            delete[] infoLog;
        }
    }
}

void Shader::destroy() {
    LOG_PRINT_DEBUG("Delete shader");

    // delete
    glDeleteShader(id);
}
