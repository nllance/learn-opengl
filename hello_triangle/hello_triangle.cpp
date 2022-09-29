#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


// Vertex shader in GLSL language, put in a C string
// Opengl version and core profile only
// The vector datatype contains 1 to 4 floats
// Since each vertex has a 3D coordinate, create a vec3 input variable with the name aPos
// gl_Position is a predefined vec4
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Fragment shader in GLSL language, put in a C string
// Output variable  defines the final colour, with the name FragColor
// RGBA (red, green, blue, alpha - opacity) representation
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";


int main(void) {
    // Initialize GLFW
    glfwInit();
    // Set opengl version to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Explicitly use core-profile, "new opengl"
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "test", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Make the context of `window` the main context on the current thread
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Size of the rendering window
    // First two params = the location of the lower left corner
    // Last two params = width and height
    // These come after the initialization of GLAD
    glViewport(0, 0, 800, 600);
    // Call on every window resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Check if shader compilation is successful
    int success;
    char error_msg[512];

    // Vertex shader
    // Create a shader object
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach the shader source code, and compile
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, error_msg);
        std::cout << "Vertex Shader Failed: " << error_msg << std::endl;
    }

    // Fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, error_msg);
        std::cout << "Fragment Shader Failed: " << error_msg << std::endl;
    }

    // Shader Program object - final linked versin of multiple shaders combined
    unsigned int shaderProgram = glCreateProgram();
    // Attach shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Delete shader objects once they are linked into the program object
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 3D coordinates within (-1, 1) - normalized device coordinates
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    // Generate a vertex array object (VAO)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate a vertex buffer object (VBO)
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Copy the vertex data into the buffer's memory
    // The type of the buffer; the size of the data; data; how to manage the data
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Tell OpenGL how it should interpret the vertex data
    // 1st param - which vertex attribute (`position` specified with `location = 0` in the vertex shader)
    // 2nd param - the size of the vertex attribute
    // 3rd param - the type of data
    // 4th param - if the data should be normalized
    // 5th param - stride, the space between consecutive vertex attributes
    // 6th param - offset, where the position data begins in the buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    // Enable the vertex attribute
    // Param - the vertex attribute location
    glEnableVertexAttribArray(0);
    // Unbind VBO and VAO
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    // Render loop, keeps running until told to stop
    // Check at the start of each loop if GLFW has been told to close
    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);
        // Rendering commands
        // Specify the colour to clear with
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Clear the colour buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the colour buffer during this render iteration and show to the screen
        // Draw the triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        // Primitive type; the starting index of the vertex array; how many vertices
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        // Check if any events are triggered (keyboard etc)
        glfwPollEvents();
    }

   // Clean everything
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteProgram(shaderProgram);
   glfwTerminate();
   return 0;
}

// When the user resizes the window, the viewport should also be resized
// This is called each time the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    // Check whether the key is currently being pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
