#include "Renderer.h"

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