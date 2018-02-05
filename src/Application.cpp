#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Static linking to GLEW
#define GLEW_STATIC

// OpenGL libs
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Debug mode
#define DEBUG

/*      ERROR HANDLING      */

// Query OpenGL for errors
#ifdef DEBUG
#define GLCall(x) \
    GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

#define ASSERT(x) if (!(x)) __builtin_trap();

// Clear errors
static void GLClearError(){
    while (glGetError() != GL_NO_ERROR);
}

// Check for errors
static bool GLLogCall(const char* function, const char* file, unsigned int line){
    while (GLenum error = glGetError()){
        std::cerr << "[OpenGL ERROR] (" << error << "): " << function << " in " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

/*      SHADER COMPILATION      */

// Shaders source codes
struct shaderProgramSource{
    std::string vertex;
    std::string fragment;
};

// Parse shader
static shaderProgramSource parseShader(const std::string& filePath){
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

// Compile shader
static unsigned int compileShader(unsigned int shaderType, const std::string& shaderSource){
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

// Create shader
static unsigned int createShader(const shaderProgramSource shaderSource){
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

    // Create vertex array object
    unsigned int vao;
    glGenVertexArrays(1, &vao);

    // Bind vertex array
    glBindVertexArray(vao);

    /*      VERTEX BUFFER     */

    // Create vertex buffer
    unsigned int vbuffer;
    glGenBuffers(1, &vbuffer);

    // Bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbuffer);

    // Setup vertex attributes
    // Position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

    // Fill buffer with data
    glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof(unsigned int), vertices, GL_STATIC_DRAW);

    // Enable vertex attribute
    glEnableVertexAttribArray(0);

    /*      INDEX BUFFER     */

    // Create index buffer object
    unsigned int ibo;
    glGenBuffers(1, &ibo);

    // Bind buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // Fill buffer with data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), indices, GL_STATIC_DRAW);

    /*      SHADERS     */

    // Setup shaders
    shaderProgramSource shaderSource = parseShader("res/shaders/basic.shader");
    unsigned int shader = createShader(shaderSource);
    glUseProgram(shader);

    /*      Uniforms        */
    
    // Locate uniforms
    int uniformLocation = glGetUniformLocation(shader, "u_color");
    ASSERT(uniformLocation != -1);
    
    // Colors
    float r = 1.0f, dr = 0.05;

    /*      GAME LOOP       */

    while (!glfwWindowShouldClose(window))
    {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Send data through uniform
        if (r > 1.0f || r < 0.0f) dr = -dr;
        r += dr;
        glUniform4f(uniformLocation, r, 0.3f, 0.8f, 1.0f);

        // Draw call for triangles
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Clean up
    glDeleteProgram(shader);
    glfwTerminate();

    return 0;
}