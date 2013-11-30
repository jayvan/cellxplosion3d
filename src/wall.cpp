#include "wall.hpp"
#include <GL/glew.h>
#include <GL/gl.h>

Wall::Wall(Point3D position, Vector3D size, double rotation) : Mover(position, size), rotation(rotation) {

}

void Wall::_update(double delta) {
  // Wall's are static!
  (void)delta;
}


void Wall::render() {
  GLfloat wall_colour[] = {1.0, 1.0, 1.0, 1.0};
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, wall_colour);
  glPushMatrix();
  glRotated(rotation, 0, 0, 1);
  glTranslated(position[0], position[1], position[2]);
  glBegin(GL_QUADS);

  // Front face
  glTexCoord2f(0, 0);
  glVertex3d(0.0, 0.0, 0.0);
  glTexCoord2f(size[0] / 4, 0);
  glVertex3d(size[0], 0.0, 0.0);
  glTexCoord2f(size[0] / 4, size[1] / 4);
  glVertex3d(size[0], size[1], 0);
  glTexCoord2f(0, size[1] / 4);
  glVertex3d(0.0, size[1], 0.0);

  // Back Face
  glTexCoord2f(0, 0);
  glVertex3d(0.0, 0.0, size[2]);
  glTexCoord2f(size[0] / 4, 0);
  glVertex3d(size[0], 0.0, size[2]);
  glTexCoord2f(size[0] / 4, size[1] / 4);
  glVertex3d(size[0], size[1], size[2]);
  glTexCoord2f(0, size[1] / 4);
  glVertex3d(0.0, size[1], size[2]);

  // Top Face
  glTexCoord2f(0, 0);
  glVertex3d(0.0, size[1], 0.0);
  glTexCoord2f(0, size[2] / 4);
  glVertex3d(0.0, size[1], size[2]);
  glTexCoord2f(size[0] / 4, size[2] / 4);
  glVertex3d(size[0], size[1], size[2]);
  glTexCoord2f(size[0] / 4, 0);
  glVertex3d(size[0], size[1], 0.0);

  // Bottom Face
  glTexCoord2f(0, 0);
  glVertex3d(0.0, 0.0, 0.0);
  glTexCoord2f(0, size[2] / 4);
  glVertex3d(0.0, 0.0, size[2]);
  glTexCoord2f(size[0] / 4, size[2] / 4);
  glVertex3d(size[0], 0.0, size[2]);
  glTexCoord2f(size[0] / 4, 0);
  glVertex3d(size[0], 0.0, 0.0);

  // Left Face
  glTexCoord2f(0, 0);
  glVertex3d(0.0, 0.0, 0.0);
  glTexCoord2f(size[1] / 4, 0.0);
  glVertex3d(0.0, size[1], 0.0);
  glTexCoord2f(size[1] / 4, size[2] / 4);
  glVertex3d(0.0, size[1], size[2]);
  glTexCoord2f(0, size[2] / 4);
  glVertex3d(0.0, 0.0, size[2]);

  // Right Face
  glTexCoord2f(0, 0);
  glVertex3d(size[0], 0.0, 0.0);
  glTexCoord2f(size[1] / 4, 0);
  glVertex3d(size[0], size[1], 0.0);
  glTexCoord2f(size[1] / 4, size[2] / 4);
  glVertex3d(size[0], size[1], size[2]);
  glTexCoord2f(0, size[2] / 4);
  glVertex3d(size[0], 0.0, size[2]);

  glEnd();
  glPopMatrix();
}
