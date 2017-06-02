#include <sstream>
#include "scene.h"

Shader* Scene::vertexShader = nullptr;
Shader* Scene::fragmentShader = nullptr;
Program* Scene::program = nullptr;
Camera* Scene::camera = nullptr;
LeftLight* Scene::leftLight = nullptr;
RightLight* Scene::rightLight = nullptr;
Object* Scene::teapot = nullptr;
Material* Scene::ceramic = nullptr;
Texture* Scene::floral = nullptr;

void Scene::setup(AAssetManager* aAssetManager) {

    // set asset manager
    Asset::setManager(aAssetManager);

    // create shaders
    vertexShader = new Shader(GL_VERTEX_SHADER, "vertex.glsl");
    fragmentShader = new Shader(GL_FRAGMENT_SHADER, "fragment.glsl");

    // create program
    program = new Program(vertexShader, fragmentShader);

    // create camera
    camera = new Camera(program);
    camera->eye = vec3(20.0f, 20.0f, 20.0f);

    // create red point light
    leftLight = new LeftLight(program);
    leftLight->position = vec3(-3.0f, 9.0f, 9.0f);

    // create blue directional light
    rightLight = new RightLight(program);
    rightLight->position = vec3(9.0f, 9.0f, -3.0f);

    // create floral texture
    floral = new Texture(program, Floral::texels, Floral::size);

    // create ceramic material
    ceramic = new Material(program, floral);

    // create teapot object
    teapot = new Object(program, ceramic, Teapot::vertices, Teapot::indices);
}

void Scene::screen(int width, int height) {

    // set camera aspect ratio
    camera->aspect = (float) width / height;
}

void Scene::update(float deltaTime) {

    // homework 2 - light movement
    lightMovement(deltaTime);

    // homework 3 - arcball
    arcball();

    // use program
    program->use();

    // update camera
    camera->update();

    // update lights
    leftLight->update();
    rightLight->update();

    // draw teapot
    teapot->draw();
}

void Scene::lightMovement(float deltaTime) {

    // start & end positions of light source movements
    const static vec3 startL = 1.0f * leftLight->position;
    const static vec3 endL   = 1.5f * leftLight->position;
    const static vec3 startR = 1.0f * rightLight->position;
    const static vec3 endR   = 1.5f * rightLight->position;

    // calculate time
    const static float moveTime = 3.0f;
    static float time = 0.0f;
    time += deltaTime;
    if (time > 2.0f * moveTime)
        time -= 2.0f * moveTime;

    // interpolation parameter
    //     0 ~  m -> 0 ~ 1
    //     m ~ 2m -> 1 ~ 0
    float p;
    if (time < moveTime)
        p = time / moveTime;
    else
        p = 2.0f - time / moveTime;

    // interpolate light source positions
    leftLight->position = (1.0f - p) * startL + p * endL;
    rightLight->position = p * startR + (1.0f - p) * endR;
}

void Scene::arcball() {

    // implement arcball
    static float last_mx, last_my;
    static float cur_mx, cur_my;

    if(Touch::motion == Touch::Motion::DOWN) {
        LOG_PRINT_DEBUG("arcball/Touch::Motion::DOWN");
        last_mx = cur_mx = Touch::position.x;
        last_my = cur_my = Touch::position.y;
    }
    if(Touch::motion == Touch::Motion::MOVE) {
        LOG_PRINT_DEBUG("arcball/Touch::Motion::MOVE");
        cur_mx = Touch::position.x;
        cur_my = Touch::position.y;

        if (cur_mx != last_mx || cur_my != last_my) {
            vec3 va = arcballVector(vec2(last_mx, last_my));
            vec3 vb = arcballVector(vec2(cur_mx, cur_my));
            float angle = acos(dot(va, vb));
            LOG_PRINT_DEBUG("arcball/angle=%f", angle);
//            mat3 camera2object = inverse(mat3(transforms[MODE_CAMERA]) *
//                                         mat3(mesh.object2world));
//            vec3 axis_in_object_coord = camera2object * axis_in_camera_coord;
//            mesh.object2world = rotate(mesh.object2world, degrees(angle), axis_in_object_coord);
            last_mx = cur_mx;
            last_my = cur_my;
        }
    }

}

vec3 Scene::arcballVector(vec2 position) {
    vec3 P = vec3(1.0 * position.x/Screen::width * 2 - 1.0,
                  1.0 * position.y/Screen::height * 2 - 1.0,
                  0);
    P.y = -P.y;
    float OP_squared = P.x * P.x + P.y * P.y;
    if (OP_squared <= 1*1)
        P.z = sqrt(1*1 - OP_squared);
    else
        P = normalize(P);

    return P;
}

