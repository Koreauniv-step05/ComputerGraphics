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


float last_mx =0, last_my = 0;
float cur_mx=0, cur_my=0;
float firstThetaFlag;

vec3 first_down_vec;
vec3 up_vec;
vec3 down_vec;

bool firstUpFlag = false;

void Scene::arcball() {
    if(Touch::motion == Touch::Motion::DOWN){
        firstThetaFlag = true;
        firstUpFlag = true;

        last_mx = cur_mx = Touch::position.x;
        last_my = cur_my = Touch::position.y;
        __android_log_print(ANDROID_LOG_DEBUG, "Motion::DOWN", "last_mx=%f, last_my=%f, cur_mx=%f, cur_my=%f",last_mx,last_my,cur_mx,cur_my);
    }

    if(Touch::motion == Touch::Motion::MOVE) {
        cur_mx = Touch::position.x;
        cur_my = Touch::position.y;
        __android_log_print(ANDROID_LOG_DEBUG, "Motion::MOVE", "last_mx=%f, last_my=%f, cur_mx=%f, cur_my=%f",last_mx,last_my,cur_mx,cur_my);

        if (last_mx != cur_mx || last_my != cur_my) {
            down_vec = arcballVector(vec2(last_mx, last_my));
            up_vec = arcballVector(vec2(cur_mx, cur_my));

            float deltaTheta;
            deltaTheta = acos(dot(up_vec, down_vec));
            teapot->worldMatrix= rotate(teapot->worldMatrix, deltaTheta, vec3(inverse(mat3(camera->viewMatrix)*mat3(teapot->worldMatrix))*cross(down_vec, up_vec)));

            last_mx = cur_mx;
            last_my = cur_my;
            if(firstThetaFlag) {
                first_down_vec = down_vec;
                firstThetaFlag = false;
            }
        }
    }
    if(Touch::motion == Touch::Motion::UP) {
        if(firstUpFlag) {
            firstUpFlag = false;
            Touch::position.x = 0;
            Touch::position.y = 0;
            last_mx = 0;
            cur_mx = 0;
            last_my = 0;
            cur_my = 0;

            float fullTheta = acos(dot(up_vec, first_down_vec));
            float fullDegree = degrees(fullTheta);
            __android_log_print(ANDROID_LOG_DEBUG, "Motion::UP",
                                "last_mx=%f, last_my=%f, cur_mx=%f, cur_my=%f", last_mx, last_my, cur_mx,
                                cur_my);
            __android_log_print(ANDROID_LOG_DEBUG, "delta_theta",
                                "deltaDegree=%f",
                                fullDegree);
        }
    }
}

vec3 Scene::arcballVector(vec2 position) {
    vec3 point = vec3(1.0 * position.x/Screen::width * 2 - 1.0,
                  1.0 * position.y/Screen::height * 2 - 1.0,
                  0);
    point.y = -point.y;
    float pw = point.x * point.x + point.y * point.y;
    if (pw <= 1*1)
        point.z = sqrt(1*1 - pw);
    else
        point = normalize(point);

    return point;
}