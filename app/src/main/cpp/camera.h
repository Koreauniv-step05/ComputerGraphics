#ifndef OPENGLES_CAMERA_H
#define OPENGLES_CAMERA_H

#include "global.h"
#include "program.h"

class Camera {

public:
    mat4 viewMatrix;
    mat4 projMatrix;
    vec3 eye;
    vec3 at;
    vec3 up;
    float fovy;
    float aspect;
    float zNear;
    float zFar;
    Camera(Program *program);
    virtual void update();

private:
    Program *program;
    virtual void create(Program* program);
};

#endif // OPENGLES_CAMERA_H
