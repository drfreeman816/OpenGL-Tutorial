#pragma once

class VertexBuffer{

    unsigned int _rendererID;

public:

    // Constructor
    // INPUT: data, size
    VertexBuffer(const void*, unsigned int);

    // Destructor
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};