#include "IndexBuffer.h"

// Constructor
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : _count(count) {

    // Create vertex buffer
    glGenBuffers(1, &_rendererID);

    // Bind buffer
    bind();

    // Fill buffer with data
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer(){
    glDeleteBuffers(1, &_rendererID);
}

// Bind buffer
void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
}

// Unbind buffer
void IndexBuffer::unbind()const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}