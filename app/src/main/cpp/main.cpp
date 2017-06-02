#include "main.h"

void surfaceCreated(AAssetManager* aAssetManager) {

    // set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // enable depth test
    glEnable(GL_DEPTH_TEST);

    // update scene
    Scene::setup(aAssetManager);
}

void surfaceChanged(int width, int height) {

    // set viewport
    glViewport(0, 0, width, height);

    // set scene screen
    Scene::screen(width, height);
}

void drawFrame(float deltaTime) {

    // clear color buffer and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // update scene
    Scene::update(deltaTime);
}

void screenSize(int width, int height) {

    // set screen size
    Screen::width = width;
    Screen::height = height;
}

void touchEvent(float x, float y, int motion) {

    // update touch position
    Touch::position.x = x;
    Touch::position.y = y;

    // update whether touch pressed
    switch (motion) {
    case 1:
        Touch::motion = Touch::Motion::DOWN;
        break;
    case 2:
        Touch::motion = Touch::Motion::MOVE;
        break;
    default:
        Touch::motion = Touch::Motion::UP;
        break;
    }
}
