#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>
#include <set>
#include <map>
#include "algebra.hpp"
#include "primitive.hpp"
#include "material.hpp"

class SceneNode {
public:
  SceneNode(const std::string& name);
  virtual ~SceneNode();

  virtual void walk_gl() const;

  const Matrix4x4& get_transform() const { return m_trans; }
  const Matrix4x4& get_inverse() const { return m_invtrans; }

  void normalize();
  virtual void normalize(Point3D& min, Point3D& max, Matrix4x4 transform);
  Vector3D get_size();
  virtual void add_keyframe(double position, double xRot, double yRot);
  virtual void animate(double delta);

  void set_transform(const Matrix4x4& m)
  {
    m_trans = m;
    m_invtrans = m.invert();
  }

  void set_transform(const Matrix4x4& m, const Matrix4x4& i)
  {
    m_trans = m;
    m_invtrans = i;
  }

  void add_child(SceneNode* child)
  {
    m_children.push_back(child);
  }


  void remove_child(SceneNode* child)
  {
    m_children.remove(child);
  }

  // Hierarchy
  typedef std::list<SceneNode*> ChildList;

  ChildList explode();
  virtual void set_texture_color(Material * new_color);

  // These will be called from Lua.
  void rotate(char axis, double angle);
  void scale(const Vector3D& amount);
  void translate(const Vector3D& amount);
  void transform(const Matrix4x4& transformation);

  // Returns true if and only if this node is a JointNode
  virtual bool is_joint() const;

protected:

  // Useful for picking
  static int next_id;
  int m_id;
  std::string m_name;

  // Transformations
  Matrix4x4 m_trans;
  Matrix4x4 m_invtrans;

  ChildList m_children;

  virtual void explode(ChildList& nodes, Matrix4x4 trans);
};

class JointNode : public SceneNode {
public:
  JointNode(const std::string& name);
  virtual ~JointNode();

  virtual void walk_gl() const;

  virtual bool is_joint() const;

  virtual void add_keyframe(double position, double xRot, double yRot);
  virtual void animate(double delta);

  void set_joint_x(double min, double init, double max);
  void set_joint_y(double min, double init, double max);

  struct JointRange {
    double min, init, max, current;
    void rotate(double delta);
  };

  struct JointKeyframe {
    double time;
    double xAngle;
    double yAngle;

    JointKeyframe(double t, double x, double y) : time(t), xAngle(x), yAngle(y) { }
  };

protected:

  JointRange m_joint_x, m_joint_y;
  std::list<JointKeyframe> keyframes;
  double maximumAnimationPos;
  double animationPos;
};

class GeometryNode : public SceneNode {
public:
  GeometryNode(const std::string& name,
               Primitive* primitive);
  virtual ~GeometryNode();

  virtual void walk_gl() const;
  virtual void normalize(Point3D& min, Point3D& max, Matrix4x4 transform);

  const Material* get_material() const;
  Material* get_material();

  virtual void set_texture_color(Material * new_color);
  void set_material(Material* material)
  {
    m_material = material;
  }

protected:
  Material* m_material;
  Primitive* m_primitive;

  virtual void explode(ChildList& nodes, Matrix4x4 trans);
};

#endif
