#include "scene.hpp"
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <stdexcept>

using namespace std;

int SceneNode::next_id = 0;

SceneNode::SceneNode(const std::string& name)
  : m_name(name)
{
  m_id = next_id++;
}

SceneNode::~SceneNode()
{
}

void SceneNode::walk_gl() const
{
  glPushMatrix();
  glMultMatrixd(m_trans.transpose().begin());
  for (ChildList::const_iterator it = m_children.begin(); it != m_children.end(); it++) {
    (*it)->walk_gl();
  }
  glPopMatrix();
}

void SceneNode::rotate(char axis, double angle)
{
  double angle_in_radians = angle * (M_PI / 180.0);
  Matrix4x4 r;

  switch (axis) {
    case 'x':
      r[1][1] = cos(angle_in_radians);
      r[1][2] = -sin(angle_in_radians);
      r[2][1] = sin(angle_in_radians);
      r[2][2] = cos(angle_in_radians);
      break;
    case 'y':
      r[0][0] = cos(angle_in_radians);
      r[0][2] = sin(angle_in_radians);
      r[2][0] = -sin(angle_in_radians);
      r[2][2] = cos(angle_in_radians);
      break;
    case 'z':
      r[0][0] = cos(angle_in_radians);
      r[0][1] = -sin(angle_in_radians);
      r[1][0] = sin(angle_in_radians);
      r[1][1] = cos(angle_in_radians);
      break;
  }

  set_transform(m_trans * r);
}

void SceneNode::scale(const Vector3D& amount)
{
  Matrix4x4 s;

  s[0][0] = amount[0];
  s[1][1] = amount[1];
  s[2][2] = amount[2];

  set_transform(m_trans * s);
}

void SceneNode::translate(const Vector3D& amount)
{
  Matrix4x4 t;

  t[0][3] = amount[0];
  t[1][3] = amount[1];
  t[2][3] = amount[2];

  set_transform(m_trans * t);
}

void SceneNode::transform(const Matrix4x4 &transformation) {
  set_transform(m_trans * transformation);
}

bool SceneNode::is_joint() const
{
  return false;
}

JointNode::JointNode(const std::string& name)
  : SceneNode(name)
{
}

JointNode::~JointNode()
{
}

void JointNode::walk_gl() const
{
  glPushMatrix();
  glMultMatrixd(m_trans.transpose().begin());
  glRotated(m_joint_x.current, 1.0, 0.0, 0.0);
  glRotated(m_joint_y.current, 0.0, 1.0, 0.0);

  for (ChildList::const_iterator it = m_children.begin(); it != m_children.end(); it++) {
    glLoadName(m_id);
    (*it)->walk_gl();
  }
  glPopMatrix();
}

bool JointNode::is_joint() const
{
  return true;
}

void JointNode::set_joint_x(double min, double init, double max)
{
  m_joint_x.min = min;
  m_joint_x.init = init;
  m_joint_x.current = init;
  m_joint_x.max = max;
}

void JointNode::set_joint_y(double min, double init, double max)
{
  m_joint_y.min = min;
  m_joint_y.init = init;
  m_joint_y.current = init;
  m_joint_y.max = max;
}

GeometryNode::GeometryNode(const std::string& name, Primitive* primitive)
  : SceneNode(name),
    m_primitive(primitive)
{
}

GeometryNode::~GeometryNode()
{
  delete m_primitive;
  delete m_material;
}

void GeometryNode::walk_gl() const
{
  glPushMatrix();
  glMultMatrixd(m_trans.transpose().begin());
  m_material->apply_gl();
  m_primitive->walk_gl();
  for (ChildList::const_iterator it = m_children.begin(); it != m_children.end(); it++) {
    (*it)->walk_gl();
  }
  glPopMatrix();
}

