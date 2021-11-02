#include "drawables/Triangle.hpp"
#include "GLFW/glfw3.h"
#include "glm/gtc/type_ptr.hpp"
#include "Transform.hpp"

Triangle::Triangle(float size, const glm::vec4& color):
    _size(size),
    _color(color)
{
}

void Triangle::draw()
{
	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(glm::value_ptr(getTransform()->getGlobalMatrix()));

    glColor4f(_color.r, _color.g, _color.b, _color.a);
    glBegin(GL_TRIANGLES);
    glVertex3f(0, _size / 2, 0);
    glVertex3f(_size / 2, -_size / 2, 0);
    glVertex3f(-_size / 2, -_size / 2, 0);
    glEnd();

    glPopMatrix();
}
