#pragma once

#include <GL/glew.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray{

    unsigned int _rendererID;

public:

    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addBuffer(const VertexBuffer&, const VertexBufferLayout&);
};