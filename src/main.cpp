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

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    g_pWindow = glfwCreateWindow(g_iWindowWidth, g_iWindowHeight,
                                 "OpenGL Window", nullptr, nullptr);

    if (!g_pWindow)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(g_pWindow);
    glfwSetFramebufferSizeCallback(g_pWindow, FramebufferSizeCallback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "GLEW initialized" << std::endl;

    glViewport(0, 0, g_iWindowWidth, g_iWindowHeight);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(g_pWindow))
    {
        ProcessInput(g_pWindow);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(g_pWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(g_pWindow);
    glfwTerminate();
    return 0;
}
