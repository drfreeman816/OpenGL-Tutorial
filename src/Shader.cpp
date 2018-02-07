#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

Shader::Shader(const std::string& filePath)
    : _rendererID(0),_filePath(filePath) {

    shaderProgramSource shaderSource = parseShader(filePath);
    _rendererID = createShader(shaderSource);

}

Shader::~Shader(){

    glDeleteProgram(_rendererID);

}

// Use shader
void Shader::bind() const{
    glUseProgram(_rendererID);
}

void Shader::unbind() const{
    glUseProgram(0);
}

 // Set uniforms

unsigned int Shader::getUniformLocation(const std::string& name){

    if(_uniformLocationCache.find(name) != _uniformLocationCache.end())
        return _uniformLocationCache[name];

    int location = glGetUniformLocation(_rendererID, name.c_str());

    _uniformLocationCache[name] = location;

    if (location == -1)
        std::cout << "WARNING: uniform '" << name << "' may not exist!" << std::endl;

    return location;
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3){
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

shaderProgramSource Shader::parseShader(const std::string& filePath){
    // Open shader file
    std::ifstream stream(filePath);
    // Shader type
    enum class shaderType{
        NONE = -1, VERTEX, FRAGMENT
    };
    // Variables
    std::string line;
    std::stringstream ss[2];
    shaderType type = shaderType::NONE;
    // Read file line by line
    while(getline(stream, line)){
        if (line.find("#shader") != std::string::npos){
            if (line.find("vertex") != std::string::npos)
                type = shaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = shaderType::FRAGMENT;
        }
        else{
            ss[(int)type] << line << '\n';
        }
    }
    // Return source code
    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::compileShader(unsigned int shaderType, const std::string& shaderSource){
    // Create shader handle
    unsigned int shader = glCreateShader(shaderType);
    // Create pointer to shader source code
    const char* shaderSourcePtr = shaderSource.c_str();
    // Specify shader source code
    glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
    // Compile shader
    glCompileShader(shader);

    // Error handling
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE){
        // Query shader compilation
        int messageLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &messageLength);
        char* message = (char*)alloca(messageLength*sizeof(char));
        glGetShaderInfoLog(shader, messageLength, &messageLength, message);
        // Output log
        std::cerr << "ERROR: Failed to compile shader!" << std::endl;
        std::cerr << message << std::endl;
        // Delete shader
        glDeleteShader(shader);
        return 0;
    }

    return shader;

}

unsigned int Shader::createShader(const shaderProgramSource shaderSource){
    // Create program handle
    unsigned int program = glCreateProgram();
    // Compile vertex shader
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, shaderSource.vertex);
    // Compile fragment shader
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, shaderSource.fragment);
    // Link shaders to the program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    // Validate program
    glValidateProgram(program);
    // Delete intermediates
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;

}