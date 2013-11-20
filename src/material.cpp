#include "material.hpp"
#include <GL/glut.h>
#include <iostream>

using namespace std;

Material::~Material()
{
}

PhongMaterial::PhongMaterial(const Colour& kd, const Colour& ks, double shininess)
  : m_kd(kd), m_ks(ks), m_shininess(shininess)
{
}

PhongMaterial::~PhongMaterial()
{
}

void PhongMaterial::apply_gl() const
{
  GLfloat diffuse_colour[] = {(float)m_kd.R(), (float)m_kd.G(), (float)m_kd.B(), 1.0};
  GLfloat specular_colour[] = {(float)m_ks.R(), (float)m_ks.G(), (float)m_ks.B(), 1.0};

  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_colour);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse_colour);
}
