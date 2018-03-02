#pragma once

#include <GL/glew.h>

#include <iostream>

// Debug mode
#define DEBUG

// Assert -> break execution
#define ASSERT(x) if (!(x)) __builtin_trap();

// Clear errors
void GLClearError();

// Check for errors
bool GLLogCall(const char*, const char*, unsigned int);

// Query OpenGL for errors
#ifdef DEBUG
#define GLCall(x) \
    GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif