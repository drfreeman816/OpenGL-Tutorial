#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

// Debug mode
//#define DEBUG

/*      ERROR HANDLING      */

// Query OpenGL for errors
#ifdef DEBUG
#define GLCall(x) \
    GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

#define ASSERT(x) if (!(x)) __builtin_trap();

// Clear errors
void GLClearError();

// Check for errors
bool GLLogCall(const char*, const char*, unsigned int);

class Renderer{

public:

    void clear() const;

    void draw(const VertexArray&, const IndexBuffer&, const Shader&) const;

};