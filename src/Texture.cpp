#include "Texture.h"

Texture::Texture(const std::string& filePath)
    : _rendererID(0), _filePath(filePath), _localBuffer(nullptr), _width(0), _height(0), _BPP(0) {

    // Load texture
    stbi_set_flip_vertically_on_load(1);                                        // Flip flag: Start image at bottom left
    _localBuffer = stbi_load(filePath.c_str(), &_width, &_height, &_BPP, 4);    // 4 channels = RGBA

    // Create OpenGL texture
    glGenTextures(1, &_rendererID);
    bind();

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Give OpenGL texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _localBuffer);

    // Unbind texture
    unbind();

    // Clear local buffer
    if (_localBuffer)
        stbi_image_free(_localBuffer);
}

Texture::~Texture(){

    glDeleteTextures(1, &_rendererID);

}

void Texture::bind(unsigned int slot) const{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _rendererID);
}

void Texture::unbind() const{
    glBindTexture(GL_TEXTURE_2D, 0);
}