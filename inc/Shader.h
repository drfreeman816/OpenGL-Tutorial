#pragma once

#include <string>
#include <unordered_map>

struct shaderProgramSource{
    std::string vertex;
    std::string fragment;
};


class Shader{

    unsigned int _rendererID;
    std::string _filePath;
    std::unordered_map<std::string, int> _uniformLocationCache;

public:

    // Constructor read shader from filepath
    Shader(const std::string&);
    ~Shader();

    // Use shader
    void bind() const;
    void unbind() const;

    // Set uniforms
    void setUniform4f(const std::string&, float, float, float, float);

private:

    shaderProgramSource parseShader(const std::string&);
    
    unsigned int compileShader(unsigned int, const std::string&);

    unsigned int createShader(const shaderProgramSource);

    unsigned int getUniformLocation(const std::string&);

};