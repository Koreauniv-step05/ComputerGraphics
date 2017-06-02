#include "program.h"

Program::Program(Shader *vertexShader, Shader *fragmentShader) {

    // create
    create();

    // attach shaders
    shader(vertexShader, fragmentShader);

    // link
    link();

    // use
    use();
}

Program::~Program() {

    // delete
    destroy();
}

void Program::create() {
    LOG_PRINT_DEBUG("Create program");

    // create
    id = glCreateProgram();

    // check id
    if (!id) {
        LOG_PRINT_ERROR("Fail to create program");
    }
}

void Program::shader(Shader* vertexShader, Shader* fragmentShader) {
    LOG_PRINT_DEBUG("Attach shaders to program");

    // attach shaders
    glAttachShader(id, vertexShader->id);
    glAttachShader(id, fragmentShader->id);
}

void Program::link() const {
    LOG_PRINT_DEBUG("Link program");

    // link
    glLinkProgram(id);

    // check link status
    GLint linkStatus;
    glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {

        // check information log length
        GLint infoLogLength;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
        if (infoLogLength) {

            // print information log
            GLchar *infoLog = new GLchar[infoLogLength];
            glGetProgramInfoLog(id, infoLogLength, NULL, infoLog);
            LOG_PRINT_ERROR("Fail to link program: \n%s", infoLog);
            delete[] infoLog;
        }
    }
}

void Program::use() const {
//    LOG_PRINT_DEBUG("Use program");

    // use
    glUseProgram(id);
}

void Program::destroy() {
    LOG_PRINT_DEBUG("Delete program");

    // delete
    glDeleteProgram(id);
}
