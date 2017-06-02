#include "camera.h"

Camera::Camera(Program* program)
        : viewMatrix(mat4(1.0f)),
          projMatrix(mat4(1.0f)),
          eye(vec3(0.0f)),
          at(vec3(0.0f)),
          up(vec3(0.0f, 1.0f, 0.0f)),
          fovy(60.0f),
          aspect(1.0f),
          zNear(1.0f),
          zFar(150.0f) {

    // create camera
    create(program);

    // update camera
    update();
}

void Camera::create(Program* program) {
    LOG_PRINT_DEBUG("Create camera");

    // set attribute
    this->program = program;

    // check uniform locations
    if (glGetUniformLocation(program->id, "viewMat") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "viewMat");
    }
    if (glGetUniformLocation(program->id, "projMat") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "projMat");
    }
}

void Camera::update() {
//    LOG_PRINT_DEBUG("Update camera");

    // update matrix
    viewMatrix = lookAt(eye, at, up);
    projMatrix = perspective(radians(fovy), aspect, zNear, zFar);

    // get uniform locations
    GLint eyePosLoc = glGetUniformLocation(program->id, "eyePos");
    GLint viewMatLoc = glGetUniformLocation(program->id, "viewMat");
    GLint projMatLoc = glGetUniformLocation(program->id, "projMat");

    // set uniform data
    if (eyePosLoc >= 0) glUniform3fv(eyePosLoc, 1, value_ptr(eye));
    if (viewMatLoc >= 0) glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, value_ptr(viewMatrix));
    if (projMatLoc >= 0) glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, value_ptr(projMatrix));
}
