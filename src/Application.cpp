#include <iostream>

// Static linking to GLEW
#define GLEW_STATIC

// OpenGL libs
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(800, 600, "OpenGL application", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize GLEW library
    if (glewInit() != GLEW_OK)
        std::cerr << "ERROR: Can't initialize GLEW library!" << std::endl;

    // Print OpenGL version
    std::cout << "Using OpenGL " << glGetString(GL_VERSION) << " by " << glGetString(GL_VENDOR) << std::endl;

    // Create vertex buffer
    unsigned int buffer;
    glGenBuffers(1, &buffer);

    // Bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // Data for triangle
    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    // Setup vertex attributes
    // Position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    // Enable vertex attrbute
    glEnableVertexAttribArray(0);

    // Fill buffer with data
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw call for triangles
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}