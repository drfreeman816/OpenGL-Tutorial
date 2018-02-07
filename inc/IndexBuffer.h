#pragma once

class IndexBuffer{

    unsigned int _rendererID;
    unsigned int _count;

public:

    // Constructor
    // INPUT: data, count
    IndexBuffer(const unsigned int*, unsigned int);

    // Destructor
    ~IndexBuffer();

    // Binding
    void bind() const;
    void unbind() const;

    // Getter
    inline unsigned int getCount() const { return _count; };
};