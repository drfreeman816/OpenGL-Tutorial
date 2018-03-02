#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <iostream>

class Renderer{

public:

    void clear() const;

    void draw(const VertexArray&, const IndexBuffer&, const Shader&) const;

};