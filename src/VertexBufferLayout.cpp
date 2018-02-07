#include "VertexBufferLayout.h"

// Push values to layout
// Float
template<>
void VertexBufferLayout::push<float>(unsigned int count){
    _elements.push_back({ GL_FLOAT, count, GL_FALSE });
    _stride += count*VertexBufferElement::getSizeOfType(GL_FLOAT);
}

// Unsigned int
template<>
void VertexBufferLayout::push<unsigned int>(unsigned int count){
    _elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    _stride += count*VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}

// Unsigned char
template<>
void VertexBufferLayout::push<unsigned char>(unsigned int count){
    _elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    _stride += count*VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}