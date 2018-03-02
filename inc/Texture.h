#pragma once

#include <GL/glew.h>

#include "vendor/stb/stb_image.h"

#include <string>

class Texture{

    unsigned int _rendererID;
    std::string _filePath;
    unsigned char* _localBuffer;
    int _width, _height, _BPP;

public:

    Texture(const std::string&);
    ~Texture();

    void bind(unsigned int = 0) const;
    void unbind() const;

    inline unsigned int getWidth() const { return _width; }
    inline unsigned int getHeight() const { return _height; }
    inline unsigned int getBPP() const { return _BPP; }

};