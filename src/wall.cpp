#include "wall.hpp"
#include <GL/gl.h>

Wall::Wall(Point3D position, Vector3D size) : Mover(position, size) {

}

void Wall::_update(double delta) {
  // Wall's dont move.
}


void Wall::render() {
  glColor3f(0.333333, 0.066667, 0.066667);
  glPushMatrix();
  glTranslated(position[0], position[1], position[2]);
  glBegin(GL_QUADS);

  // Front face
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(size[0], 0.0, 0.0);
  glVertex3d(size[0], size[1], 0.0);
  glVertex3d(0.0, size[1], 0.0);

  // Back Face
  glVertex3d(0.0, 0.0, size[2]);
  glVertex3d(size[0], 0.0, size[2]);
  glVertex3d(size[0], size[1], size[2]);
  glVertex3d(0.0, size[1], size[2]);

  // Top Face
  glVertex3d(0.0, size[1], 0.0);
  glVertex3d(0.0, size[1], size[2]);
  glVertex3d(size[0], size[1], size[2]);
  glVertex3d(size[0], size[1], 0.0);

  // Bottom Face
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, 0.0, size[2]);
  glVertex3d(size[0], 0.0, size[2]);
  glVertex3d(size[0], 0.0, 0.0);

  // Left Face
  glVertex3d(0.0, 0.0, 0.0);
  glVertex3d(0.0, size[1], 0.0);
  glVertex3d(0.0, size[1], size[2]);
  glVertex3d(0.0, 0.0, size[2]);

  // Right Face
  glVertex3d(size[0], 0.0, 0.0);
  glVertex3d(size[0], size[1], 0.0);
  glVertex3d(size[0], size[1], size[2]);
  glVertex3d(size[0], 0.0, size[2]);

  glEnd();
  glPopMatrix();
}
