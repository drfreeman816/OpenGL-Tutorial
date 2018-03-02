#include "VertexBuffer.h"

// Constructor
VertexBuffer::VertexBuffer(const void* data, unsigned int size){

    glGenBuffers(1, &_rendererID);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &_rendererID);
}

// Bind buffer
void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
}

// Unbind buffer
void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}