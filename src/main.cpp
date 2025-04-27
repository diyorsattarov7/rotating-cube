// clang-format off
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>
#include <cmath>
#include <ctime>
#include <iostream>

int g_iWindowWidth = 1000, g_iWindowHeight = 800;
GLFWwindow *g_pWindow = nullptr;
clock_t g_PreviousTicks, g_CurrentTicks;
float g_fRotationRate = 50.0f;
float g_fRotate1 = 0.0f;

void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
void ProcessInput(GLFWwindow *window);
void DrawUnitSquare();
void UpdateDeltaTime();

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    if (height == 0) height = 1;
    g_iWindowWidth = width;
    g_iWindowHeight = height;
    glViewport(0, 0, width, height);
    glLoadIdentity();
    gluPerspective(60.0f, (double)width / height, 0.1, 100.0);
}

void ProcessInput(GLFWwindow *window) { if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true); }

void UpdateDeltaTime()
{
    g_CurrentTicks = clock();
    float deltaTicks = (float)(g_CurrentTicks - g_PreviousTicks);
    g_PreviousTicks = g_CurrentTicks;
    float fDeltaTime = deltaTicks / (float)CLOCKS_PER_SEC;
    g_fRotate1 += (10 * g_fRotationRate * fDeltaTime);
    g_fRotate1 = fmodf(g_fRotate1, 360.0f);
}

void DrawUnitSquare()
{
    glBegin(GL_QUADS);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
}

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
                                 "Rotating Square Render", nullptr, nullptr);

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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)g_iWindowWidth / g_iWindowHeight, 0.1, 100.0);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    g_PreviousTicks = clock();

    while (!glfwWindowShouldClose(g_pWindow))
    {
        ProcessInput(g_pWindow);
        UpdateDeltaTime();

        glClear(GL_COLOR_BUFFER_BIT);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, -6.0f);
    
        glRotatef(g_fRotate1, 0.0f, 1.0f, 0.0f);

        glColor3f(1.0f, 0.0f, 0.0f);
        DrawUnitSquare();

        glfwSwapBuffers(g_pWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(g_pWindow);
    glfwTerminate();
    return 0;
}
