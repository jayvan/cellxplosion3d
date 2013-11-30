#ifndef CS488_MATERIAL_HPP
#define CS488_MATERIAL_HPP

#include "algebra.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

class Material {
public:
  virtual ~Material();
  virtual void apply_gl() const = 0;
  virtual bool is_texture() const;
  virtual void set_color(Material* newColor) {(void)newColor;}

protected:
  Material()
  {
  }
};

class PhongMaterial : public Material {
public:
  PhongMaterial(const Colour& kd, const Colour& ks, double shininess);
  virtual ~PhongMaterial();

  virtual void apply_gl() const;

private:
  Colour m_kd;
  Colour m_ks;

  double m_shininess;
};

class TextureMaterial : public Material {
public:
  TextureMaterial(const char* filename, Material* color);
  virtual ~TextureMaterial();
  virtual bool is_texture() const;
  virtual void set_color(Material* newColor);

  virtual void apply_gl() const;

private:
  GLuint texture;
  Material* color;

};


#endif
