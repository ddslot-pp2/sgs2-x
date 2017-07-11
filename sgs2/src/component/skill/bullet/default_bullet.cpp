#include "default_bullet.h"

using super = bullet;

default_bullet::default_bullet(object* obj, const vector3& dir, const vector3& size, float speed, float distance, float power)
    : bullet(obj, dir, size, speed, distance, power)
{

}

default_bullet::~default_bullet()
{

}

void default_bullet::update(float delta)
{
    super::update(delta);
}

void default_bullet::destroy() const
{

}