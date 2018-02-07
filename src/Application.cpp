// Static linking to GLEW
#define GLEW_STATIC

// OpenGL libs
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Standard libs
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Abstracted OpenGL
#include "Renderer.h"
#include "VertexBufferLayout.h"

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(800, 800, "OpenGL application", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Select OpenGL version and profile
    // OpenGL 3.3 CORE
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // VSync
    glfwSwapInterval(1);

    // Initialize GLEW library
    if (glewInit() != GLEW_OK)
        std::cerr << "ERROR: Can't initialize GLEW library!" << std::endl;

    // Print OpenGL version
    std::cout << "Using OpenGL " << glGetString(GL_VERSION) << " by " << glGetString(GL_VENDOR) << std::endl;

    /*      DATA      */
    // Vertices
    float vertices[] = {
    //  x      y
        -0.5f, -0.5f,   // 0
         0.5f, -0.5f,   // 1
         0.5f,  0.5f,   // 2
        -0.5f,  0.5f    // 3
    };
    // Indices
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    /*      VERTEX ARRAY     */

    // Create vertex array
    VertexArray va;

    /*      VERTEX BUFFER     */

    // Create vertex buffer
    VertexBuffer vb(vertices, 4*2*sizeof(unsigned int));

    // Setup vertex layout
    VertexBufferLayout layout;
    layout.push<float>(2);

    // Add vertex buffer to vertex array
    va.addBuffer(vb, layout);

    /*      INDEX BUFFER     */

    // Create index buffer object
    IndexBuffer ib(indices, 2*3);

    /*      SHADERS     */

    // Setup shaders
    Shader shader("res/shaders/basic.shader");
    shader.bind();

    /*      Uniforms        */
    
    // Locate uniforms
    shader.setUniform4f("u_color",  0.8f, 0.3f, 0.8f, 1.0f);
    
    // Colors
    float r = 1.0f, dr = 0.05;

    /*      UNBIND EVERYTHING       */

    va.unbind();
    vb.unbind();
    ib.unbind();
    shader.unbind();

    /*      RENDERER       */

    Renderer renderer;

    /*      GAME LOOP       */

    while (!glfwWindowShouldClose(window))
    {
        // Render here
        renderer.clear();

        // Send data through uniform
        shader.bind();
        if (r > 1.0f || r < 0.0f) dr = -dr;
        r += dr;
        shader.setUniform4f("u_color",  r, 0.3f, 0.8f, 1.0f);

        // Draw call for triangles
        renderer.draw(va, ib, shader);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up
    glfwTerminate();

    return 0;
}