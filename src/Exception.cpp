#include "Exception.h"

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