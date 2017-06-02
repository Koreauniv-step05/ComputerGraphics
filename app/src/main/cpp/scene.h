#ifndef OPENGLES_SCENE_H
#define OPENGLES_SCENE_H

#include "global.h"
#include "input.h"
#include "program.h"
#include "camera.h"
#include "light.h"
#include "object.h"
#include "material.h"
#include "teapot.h"
#include "floral.h"

class Scene {

private:
    static Shader* vertexShader;
    static Shader* fragmentShader;
    static Program* program;
    static Camera* camera;
    static LeftLight* leftLight;
    static RightLight* rightLight;
    static Object* teapot;
    static Material* ceramic;
    static Texture* floral;

public:
    static void setup(AAssetManager* aAssetManager);
    static void screen(int width, int height);
    static void update(float deltaTime);

private:
    static void lightMovement(float deltaTime);
    static void arcball();
    static vec3 arcballVector(vec2 position);
};

#endif // OPENGLES_SCENE_H
