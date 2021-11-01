#include "main.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>

int main(int argc, char* argv[])
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DOUBLEBUFFER);
    glDepthFunc(GL_LESS);

    glClearColor(0, 0, 0, 1);

    glm::mat4 m = glm::perspective(45.0f, 4.0f / 3.0f, 1.0f, 100.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(m));

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor4f(1, 0, 0, 1);
        glBegin(GL_TRIANGLES);
        glVertex3f(0, 0.5, -5);
        glVertex3f(0.5, -0.5, -5);
        glVertex3f(-0.5, -0.5, -5);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}