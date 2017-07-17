#include "collider.h"
#define _USE_MATH_DEFINES 
#include <cmath>  

collider::collider(const vector3& pos, const vector3& size, float degree) : pos_(pos), size_(size), degree_(degree), rect_area_(size.X * size.Z)
{
    wprintf(L"콜콜콜\n");
    constexpr static auto max_point_size = 4;

    vector3 points[max_point_size] = {};
    points[0] = vector3(pos_.X + (size_.X / 2.0f), 0.0f, pos_.Z + (size_.Z / 2.0f));
    points[1] = vector3(pos_.X + (size_.X / 2.0f), 0.0f, pos_.Z - (size_.Z / 2.0f));
    points[2] = vector3(pos_.X - (size_.X / 2.0f), 0.0f, pos_.Z - (size_.Z / 2.0f));
    points[3] = vector3(pos_.X - (size_.X / 2.0f), 0.0f, pos_.Z + (size_.Z / 2.0f));

    for (auto i = 0; i < max_point_size; ++i)
    {
        auto rot_point = rotate_point(pos_.X, pos_.Z, degree, points[i]);
        //wprintf(L"before x: %f, z: %f\n", points[i].X, points[i].Z);
        wprintf(L"after  x: %f, z: %f\n", rot_point.X, rot_point.Z);
        points_.emplace_back(rot_point);
    }
}

vector3 collider::rotate_point(float cx, float cz, float degree, const vector3 p) const
{
    // 시계방향 회전
    auto angle = degree * (3.14159f / 180.0f) * -1.0f;

    return vector3(
        cos(angle) * (p.X - cx) - sin(angle) * (p.Z - cz) + cx,
        0.0f,
        sin(angle) * (p.X - cx) + cos(angle) * (p.Z - cz) + cz
    );
};

bool collider::check_intersection(const vector3& other_pos, const vector3& other_size) const
{
    const auto A = points_[0];
    const auto B = points_[1];
    const auto C = points_[2];
    const auto D = points_[3];

    const auto P = other_pos;

    wprintf(L"other pos X: %f, Z: %f\n", other_pos.X, other_pos.Z);

    const auto& triarea_0 = triangle_area(A, P, D);
    const auto& triarea_1 = triangle_area(D, P, C);
    const auto& triarea_2 = triangle_area(C, P, B);
    const auto& triarea_3 = triangle_area(P, B, A);

    if (rect_area_ < (triarea_0 + triarea_1 + triarea_2 + triarea_3))
    {
        return false;
    }
 

    return true;
}

float collider::triangle_area(const vector3& a, const vector3& b, const vector3& c) const
{
    return fabs((a.X - c.X) * (b.Z - a.Z) - (a.X - b.X) * (c.Z - a.Z)) * 0.5f;
}
