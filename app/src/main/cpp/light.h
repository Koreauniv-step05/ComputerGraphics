#ifndef OPENGLES_LIGHT_H
#define OPENGLES_LIGHT_H

#include "global.h"
#include "program.h"

class Light {

public:
    vec3 position;
    float attenuation[3];
    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
    Light(Program* program);
    virtual void update() const;

protected:
    Program* program;
    virtual void create(Program* program);
};

class LeftLight : public Light {
public:
    LeftLight(Program *program);
    virtual void update() const override;

protected:
    virtual void create(Program* program) override;
};

class RightLight : public Light {
public:
    RightLight(Program *program);
    virtual void update() const override;

protected:
    virtual void create(Program* program) override;
};

#endif // OPENGLES_LIGHT_H
