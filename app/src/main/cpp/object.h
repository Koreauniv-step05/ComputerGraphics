#ifndef OPENGLES_OBJECT_H
#define OPENGLES_OBJECT_H

#include "global.h"
#include "program.h"
#include "material.h"

class Object {

public:
    mat4 worldMatrix;
    Object(Program* program, Material* material,
           const vector<Vertex>& vertices, const vector<Index>& indices);
    virtual ~Object();
    virtual void draw() const;

private:
    Program* program;
    Material* material;
    GLuint vbo;
    GLuint ibo;
    vector<Vertex> vertices;
    vector<Index> indices;
    virtual void create(Program* program, Material* material);
    virtual void data(const vector<Vertex>& vertices, const vector<Index>& indices);
    virtual void destroy();
};

#endif // OPENGLES_OBJECT_H
