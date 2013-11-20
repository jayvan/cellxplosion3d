#include "primitive.hpp"
#include <iostream>

using namespace std;

SphereRenderer Sphere::renderer = SphereRenderer();
CylinderRenderer Cylinder::renderer = CylinderRenderer();
DiskRenderer Disk::renderer = DiskRenderer();
TetrahedronRenderer Tetrahedron::renderer = TetrahedronRenderer();

Primitive::~Primitive()
{
}

Sphere::Sphere() {

}

Sphere::~Sphere()
{
}

void Sphere::walk_gl() const
{
  renderer.render();
}

SphereRenderer::SphereRenderer() {
}

void SphereRenderer::render() {
  // Initialise a displayList if we haven't made one yet
  if (list == 0) {
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
      gluSphere(quadric, 1.0, 100, 100);
    glEndList();
  }

  glCallList(list);
}

Cylinder::Cylinder() {

}

Cylinder::~Cylinder()
{
}

void Cylinder::walk_gl() const
{
  renderer.render();
}

CylinderRenderer::CylinderRenderer() {
}

void CylinderRenderer::render() {
  // Initialise a displayList if we haven't made one yet
  if (list == 0) {
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
      gluCylinder(quadric, 1.0, 1.0, 1.0, 100, 100);
    glEndList();
  }

  glCallList(list);
}


Disk::Disk() {

}

Disk::~Disk()
{
}

void Disk::walk_gl() const
{
  renderer.render();
}

DiskRenderer::DiskRenderer() {
}

void DiskRenderer::render() {
  // Initialise a displayList if we haven't made one yet
  if (list == 0) {
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
      gluDisk(quadric, 0.0, 1.0, 100, 100);
    glEndList();
  }

  glCallList(list);
}

Tetrahedron::Tetrahedron() {

}

Tetrahedron::~Tetrahedron()
{
}

void Tetrahedron::walk_gl() const
{
  renderer.render();
}

TetrahedronRenderer::TetrahedronRenderer() {
}

void TetrahedronRenderer::render() {
  // Initialise a displayList if we haven't made one yet
  if (list == 0) {
    GLUquadric *quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
      glBegin(GL_TRIANGLE_STRIP);
        double one_over_root_two = 1 / sqrt(2);
        glVertex3f(1.0, 0.0, -one_over_root_two);
        glVertex3f(-1.0, 0.0, -one_over_root_two);
        glVertex3f(0.0, 1.0, one_over_root_two);
        glVertex3f(0.0, -1.0, one_over_root_two);
        glVertex3f(1.0, 0.0, -one_over_root_two);
        glVertex3f(-1.0, 0.0, -one_over_root_two);
      glEnd();
    glEndList();
  }

  glCallList(list);
}
