#ifndef OPENGLES_PROGRAM_H
#define OPENGLES_PROGRAM_H

#include "global.h"
#include "shader.h"

class Program {

public:
    GLuint id;
    Program(Shader* vertexShader, Shader* fragmentShader);
    virtual ~Program();
    virtual void use() const;

private:
    virtual void create();
    virtual void shader(Shader* vertexShader, Shader* fragmentShader);
    virtual void link() const;
    virtual void destroy();
};

#endif // OPENGLES_PROGRAM_H
