#ifndef __COLLIDER_H
#define __COLLIDER_H

#include "../../../core/src/util/vector3.h"
#include <vector>

class collider
{
public:
    collider(const vector3& pos, const vector3& size, float degree_);
    bool check_intersection(const vector3& other_pos, const vector3& other_size);

    bool point_in_triangle(vector3 pt, vector3 v1, vector3 v2, vector3 v3);
    vector3 rotate_point(float cx, float cz, float degree, const vector3 p) const;
    float triangle_area(const vector3& a, const vector3& b, const vector3& c) const;

    vector3 pos_;
    vector3 size_;
    float degree_;
    std::vector<vector3> points_;
    float rect_area_;
};

#endif
