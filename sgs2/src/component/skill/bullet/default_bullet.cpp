#include "default_bullet.h"

using super = bullet;

default_bullet::default_bullet(object* obj, const vector3& dir, const vector3& size, float speed, float distance, float power)
    : bullet(obj, dir, size, speed, distance, power)
{

}

default_bullet::~default_bullet()
{
    wprintf(L"default bullet 소멸자 호출\n");
}

void default_bullet::update(float delta)
{
    super::update(delta);
}

void default_bullet::destroy() const
{
    super::destroy();
}
