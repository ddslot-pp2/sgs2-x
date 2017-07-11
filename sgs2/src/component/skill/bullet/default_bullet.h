#ifndef __DEFAULT_BULLET
#define __DEFAULT_BULLET

#include "bullet.h"

class default_bullet : public bullet
{
public:
    explicit default_bullet(object* obj, const vector3& dir, const vector3& size, float speed, float distance, float power);
    virtual ~default_bullet();

    void update(float delta) override;
    void destroy() const override;
};


#endif
