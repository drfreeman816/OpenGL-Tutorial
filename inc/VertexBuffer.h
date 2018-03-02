#pragma once

#include <GL/glew.h>


class VertexBuffer{

    unsigned int _rendererID;

public:

    // Constructor
    // INPUT: data, size
    VertexBuffer(const void*, unsigned int);

    // Destructor
    ~VertexBuffer();

    // Bind/Unbind buffer
    void bind() const;
    void unbind() const;
    
};