#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);


int main(void) {
    // Initialize GLFW
    glfwInit();
    // Set opengl version to use
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // Explicitly use core-profile, "new opengl"
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window object
    GLFWwindow* window = glfwCreateWindow(800, 600, "test", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Mkae the context of `window` the main context on the current thread
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Size of the rendering window
    // First two params = the location of the lower left corner
    // Last two params = width and height
    glViewport(0, 0, 800, 600);
    // Call on every window resize
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

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
        glfwSwapBuffers(window);
        // Check if any events are triggered (keyboard etc)
        glfwPollEvents();
    }

    /* Double buffer
       When an application draws in a single buffer, the resulting
       image may display flickering issues. This is because the
       resulting output image is not drawn in an instant, but drawn
       pixel by pixel and usually from left to right and top to
       bottom. Because this image is not displayed at an instant
       to the user while still being rendered to, the result may
       contain artifacts. To circumvent these issues, windowing
       applications apply a double buffer for rendering. The front
       buffer contains the final output image that is shown at the
       screen, while all the rendering commands draw to the back
       buffer. As soon as all the rendering commands are finished
       we swap the back buffer to the front buffer so the image
       can be displayed without still being rendered to, removing
       all the aforementioned artifacts.
    */

   // Clean everything
   glfwTerminate();
   return 0;
}

// When the user resizes the window, the viewport should also be resized
// This is called each time the window is resized
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    // Check whether the key is currently being pressed
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
