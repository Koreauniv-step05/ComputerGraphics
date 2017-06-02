#include "object.h"

Object::Object(Program* program, Material* material,
               const vector<Vertex>& vertices, const vector<Index>& indices)
        : worldMatrix(mat4(1.0f)) {

    // create
    create(program, material);

    // set data
    data(vertices, indices);

    // draw
    draw();
}

Object::~Object() {

    // destroy
    destroy();
}

void Object::create(Program* program, Material* material) {
    LOG_PRINT_DEBUG("Create object");

    // set attributes
    this->program = program;
    this->material = material;

    // generate buffer objects
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

    // check buffer object ID
    if (!vbo || !ibo) {
        LOG_PRINT_ERROR("Fail to generate buffer");
    }

    // check world matrix uniform location
    if (glGetUniformLocation(program->id, "worldMat") < 0) {
        LOG_PRINT_WARN("Fail to get uniform location: %s", "worldMat");
    }
}

void Object::data(const vector<Vertex>& vertices, const vector<Index>& indices) {
    LOG_PRINT_DEBUG("Set object data");

    // set attributes
    this->vertices = vertices;
    this->indices = indices;

    // bind buffer objects
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // set buffer data
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(),
                 vertices.data(), GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index) * indices.size(),
                 indices.data(), GL_STATIC_DRAW);
}

void Object::draw() const {
//    LOG_PRINT_DEBUG("Draw object");

    // update material
    material->update();

    // get world matrix uniform location
    GLint loc = glGetUniformLocation(program->id, "worldMat");

    // set world matrix uniform data
    if (loc >= 0) glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(worldMatrix));

    // bind buffer objects
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // enable vertex attribute arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // set vertex attribute pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (const void *) offsetof(Vertex, position));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (const void *) offsetof(Vertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (const void *) offsetof(Vertex, texture));

    // draw elements
    glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_SHORT, (const void *) 0);
}

void Object::destroy() {
    LOG_PRINT_DEBUG("Delete object");

    // delete buffer objects
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
}
