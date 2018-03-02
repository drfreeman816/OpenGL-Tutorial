#pragma once

#include <vector>

#include <GL/glew.h>

#include "Exception.h"

struct VertexBufferElement{

    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int getSizeOfType(unsigned int type){
        switch (type){
            case GL_FLOAT:          return sizeof(GLfloat);
            case GL_UNSIGNED_INT:   return sizeof(GLuint);
            case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout{

    std::vector<VertexBufferElement> _elements;
    unsigned int _stride;

public:

    VertexBufferLayout()
        : _stride(0) {}

    // Push values to layout
    template<typename T>
    void push (unsigned int count){
        //static_assert(false);
    }

    // Getters
    inline const std::vector<VertexBufferElement> getElements() const { return _elements; }
    inline unsigned int getStride() const { return _stride; }

};