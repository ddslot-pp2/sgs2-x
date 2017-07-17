#ifndef __COLLIDER_H
#define __COLLIDER_H

#include "../../../core/src/util/vector3.h"

class collider
{
public:
    collider(const vector3& pos, const vector3& size);
    bool check_intersection(const vector3& other_pos, const vector3& other_size) const;

    vector3 pos_;
    vector3 size_;
};

#endif
