#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray{

    unsigned int _rendererID;

public:

    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addBuffer(const VertexBuffer&, const VertexBufferLayout&);
};