#include "VertexBuffer.h"

#include "Renderer.h"

// Constructor
VertexBuffer::VertexBuffer(const void* data, unsigned int size){

    // Create vertex buffer
    glGenBuffers(1, &_rendererID);

    // Bind buffer
    bind();

    // Fill buffer with data
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