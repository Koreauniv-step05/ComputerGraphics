#ifndef OPENGLES_MATERIAL_H
#define OPENGLES_MATERIAL_H

#include "global.h"
#include "program.h"
#include "texture.h"

class Material {

public:
    vec3 specular;
    vec3 ambient;
    vec3 emissive;
    float shininess;
    Material(Program* program, Texture* texture = nullptr);
    virtual void update() const;

private:
    Program* program;
    Texture* texture;
    virtual void create(Program* program, Texture* texture);
};

#endif // OPENGLES_MATERIAL_H
