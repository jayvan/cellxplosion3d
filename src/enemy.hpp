#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "algebra.hpp"
#include "mover.hpp"
#include "scene.hpp"
#include "explosion.hpp"
#include <string>

class Enemy : public Mover {
  class Limb : public Mover {
    SceneNode* node;
    double rotation;

  public:
    Limb(SceneNode* node, Point3D position, Vector3D vel);
    void render();


  protected:
    void _update(double delta);
  };

  std::string number;
  double speed;
  unsigned int digitIndex;
  double rotation;
  double timeLeft;
  bool destroyed;
  SceneNode* node;
  Mover& target;
  std::list<Limb*> limbs;
  Explosion explosion;

protected:
  void _update(double delta);

public:
  Enemy();
  Enemy(Point3D position, Mover& target, double speedBoost, unsigned int numberBoost);
  ~Enemy();
  void render();
  bool tryDigit(char num);
  void advanceDigit();
  void resetDigit();
  bool tryDestroy();
  bool isGone();
  void destroy(); // Public for god mode
};

#endif
