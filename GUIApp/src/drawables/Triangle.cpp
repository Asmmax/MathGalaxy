#include "drawables/Triangle.hpp"
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

Triangle::Triangle():
    _projectionMatrix(glm::perspective(45.0f, 4.0f / 3.0f, 1.0f, 100.0f))
{
}

void Triangle::draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(_projectionMatrix));

    glColor4f(1, 0, 0, 1);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0.5, -5);
    glVertex3f(0.5, -0.5, -5);
    glVertex3f(-0.5, -0.5, -5);
    glEnd();
}
