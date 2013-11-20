#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include "algebra.hpp"
#include <GL/glut.h>

class Primitive {
public:
  virtual ~Primitive();
  virtual void walk_gl() const = 0;
};

class SphereRenderer {
  public:
    SphereRenderer();
    void render();
  private:
    GLuint list;
};

class Sphere : public Primitive {
public:
  Sphere();
  virtual ~Sphere();
  virtual void walk_gl() const;
private:
  static SphereRenderer renderer;
};

class CylinderRenderer {
  public:
    CylinderRenderer();
    void render();
  private:
    GLuint list;
};

class Cylinder : public Primitive {
public:
  Cylinder();
  virtual ~Cylinder();
  virtual void walk_gl() const;
private:
  static CylinderRenderer renderer;
};

class DiskRenderer {
  public:
    DiskRenderer();
    void render();
  private:
    GLuint list;
};

class Disk : public Primitive {
public:
  Disk();
  virtual ~Disk();
  virtual void walk_gl() const;
private:
  static DiskRenderer renderer;
};

class TetrahedronRenderer {
  public:
    TetrahedronRenderer();
    void render();
  private:
    GLuint list;
};

class Tetrahedron : public Primitive {
public:
  Tetrahedron();
  virtual ~Tetrahedron();
  virtual void walk_gl() const;
private:
  static TetrahedronRenderer renderer;
};

#endif
