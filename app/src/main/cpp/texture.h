#ifndef OPENGLES_TEXTURE_H
#define OPENGLES_TEXTURE_H

#include "global.h"
#include "program.h"

class Texture {
public:
    Texture(Program* program, const vector<Texel>& texels, const GLsizei size);
    virtual ~Texture();
    virtual void update() const;

private:
    GLuint id;
    Program* program;
    virtual void create(Program *program);
    virtual void data(const vector<Texel>& texels, const GLsizei size);
    virtual void destroy();
};

#endif // OPENGLES_TEXTURE_H
