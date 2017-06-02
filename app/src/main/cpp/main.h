#ifndef OPENGLES_MAIN_H
#define OPENGLES_MAIN_H

#include "global.h"
#include "input.h"
#include "scene.h"

void surfaceCreated(AAssetManager* aAssetManager);
void surfaceChanged(int width, int height);
void drawFrame(float deltaTime);
void screenSize(int width, int height);
void touchEvent(float x, float y, int motion);

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_surfaceCreated(JNIEnv *env, jobject instance,
                                                            jobject assetManager) {
    // call native function
    surfaceCreated(AAssetManager_fromJava(env, assetManager));
}

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_surfaceChanged(JNIEnv *env, jobject instance,
                                                            jint width, jint height) {
    // call native function
    surfaceChanged(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_drawFrame(JNIEnv *env, jobject instance,
                                                       jfloat deltaTime) {
    // call native function
    drawFrame(deltaTime);
}

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_screenSize(JNIEnv *env, jobject instance,
                                                        jint width, jint height) {
    // call native function
    screenSize(width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_kr_ac_korea_media_opengles_MainActivity_touchEvent(JNIEnv *env, jobject instance,
                                                        jfloat x, jfloat y, jint motion) {
    // call native function
    touchEvent(x, y, motion);
}

#endif // OPENGLES_MAIN_H
