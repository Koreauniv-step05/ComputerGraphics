#ifndef OPENGLES_INPUT_H
#define OPENGLES_INPUT_H

#include "global.h"

class Screen {
public:
    static int width;
    static int height;
};

class Touch {
public:
    enum class Motion {DOWN, MOVE, UP};
    static Motion motion;
    static vec2 position;
};

#endif // OPENGLES_INPUT_H
