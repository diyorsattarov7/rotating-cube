// clang-format off
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int g_iWindowWidth = 1000, g_iWindowHeight = 800;
GLFWwindow *g_pWindow = nullptr;

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    if (height == 0) height = 1;
    g_iWindowWidth = width;
    g_iWindowHeight = height;
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow *window) { if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true); }

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    
    std::cout << "GLFW initialized" << std::endl;
}
