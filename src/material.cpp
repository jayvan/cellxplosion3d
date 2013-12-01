#include "material.hpp"
#include "shader.hpp"
#include <SOIL.h>
#include <GL/glut.h>
#include <iostream>

extern shaderProgram g_shader;

using namespace std;

Material::~Material()
{
}

bool Material::is_texture() const {
  return false;
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
  glBindTexture(GL_TEXTURE_2D, 0);

  GLfloat diffuse_colour[] = {(float)m_kd.R(), (float)m_kd.G(), (float)m_kd.B(), 1.0};
  GLfloat specular_colour[] = {(float)m_ks.R(), (float)m_ks.G(), (float)m_ks.B(), 1.0};

  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_colour);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffuse_colour);
  g_shader.setActive(shaderProgram::SPECULAR);
}

TextureMaterial::TextureMaterial(const char* filename, Material* color) {
  texture = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS);
  TextureMaterial::color = color;
}

TextureMaterial::~TextureMaterial() {
}

void TextureMaterial::set_color(Material* newColor) {
  color = newColor;
}

bool TextureMaterial::is_texture() const {
  return true;
}

void TextureMaterial::apply_gl() const {
  color->apply_gl();
  glBindTexture(GL_TEXTURE_2D, texture);
  g_shader.setActive(shaderProgram::TEXTURE);
}
