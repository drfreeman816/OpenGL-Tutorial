#include "VertexArray.h"

// Constructor
VertexArray::VertexArray(){

    glGenVertexArrays(1, &_rendererID);
    bind();

}

// Destructor
VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &_rendererID);
}

void VertexArray::bind() const{
    glBindVertexArray(_rendererID);
}

void VertexArray::unbind() const{
    glBindVertexArray(0);
}

// Add a vertex buffer with specified layout
void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout){

    // Bind vertex array
    bind();

    // Bind vertex buffer
    vb.bind();

    // Setup layout for vertex buffer
    const auto& elements = layout.getElements();

    unsigned int offset = 0;

    for (unsigned int i = 0; i < elements.size(); i++){

        const auto& element = elements[i];
        // Enable vertex attribute
        glEnableVertexAttribArray(i);
        // Setup vertex attributes
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*) offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
        
    }


}