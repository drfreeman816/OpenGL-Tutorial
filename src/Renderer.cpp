#include "Renderer.h"

#include <iostream>

// Clear errors
void GLClearError(){
    while (glGetError() != GL_NO_ERROR);
}

// Check for errors
bool GLLogCall(const char* function, const char* file, unsigned int line){
    while (GLenum error = glGetError()){
        std::cerr << "[OpenGL ERROR] (" << error << "): " << function << " in " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

// Clear
void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

// Draw
void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const{

    shader.bind();
    va.bind();
    ib.bind();

    // Draw call
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);

}