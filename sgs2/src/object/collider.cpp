#include "collider.h"
#define _USE_MATH_DEFINES 
#include <cmath>  

collider::collider(const vector3& pos, const vector3& size, float degree) : pos_(pos), size_(size), degree_(degree), rect_area_(size.X * size.Z)
{
 
    vector3 points[4] = {};
    points[0] = vector3(pos_.X + (size_.X / 2.0f), 0.0f, pos_.Z + (size_.Z / 2.0f));
    points[1] = vector3(pos_.X + (size_.X / 2.0f), 0.0f, pos_.Z - (size_.Z / 2.0f));
    points[2] = vector3(pos_.X - (size_.X / 2.0f), 0.0f, pos_.Z - (size_.Z / 2.0f));
    points[3] = vector3(pos_.X - (size_.X / 2.0f), 0.0f, pos_.Z + (size_.Z / 2.0f));

    for (auto i = 0; i < 4; ++i)
    {
        auto rot_point = rotate_point(pos_.X, pos_.Z, degree, points[i]);
        wprintf(L"before x: %f, z: %f\n", points[i].X, points[i].Z);
        wprintf(L"after  x: %f, z: %f\n", rot_point.X, rot_point.Z);
        points_.emplace_back(rot_point);
    }
 
}

vector3 collider::rotate_point(float cx, float cz, float degree, const vector3 p) const
{
    // 시계방향 회전
    auto angle = degree * (3.14159f / 180.0f) * -1.0f;

    return vector3(
        (cos(angle) * (p.X - cx)) - (sin(angle) * (p.Z - cz)) + cx,
        0.0f,
        (sin(angle) * (p.X - cx)) + (cos(angle) * (p.Z - cz)) + cz
    );
};

bool collider::point_in_triangle(vector3 pt, vector3 v1, vector3 v2, vector3 v3)
{
    auto sign = [](vector3 p1, vector3 p2, vector3 p3)
    {
        return (p1.X - p3.X) * (p2.Z - p3.Z) - (p2.X - p3.X) * (p1.Z - p3.Z);
    };

    bool b1, b2, b3;

    b1 = sign(pt, v1, v2) < 0.0f;
    b2 = sign(pt, v2, v3) < 0.0f;
    b3 = sign(pt, v3, v1) < 0.0f;

    return ((b1 == b2) && (b2 == b3));
}

bool collider::check_intersection(const vector3& other_pos, const vector3& other_size) 
{
    //auto other_pos2 = vector3(105.0f, 0.0f, 0.0f);

    if (point_in_triangle(other_pos, points_[0], points_[1], points_[2]))
    {
        return true;
    }

    if (point_in_triangle(other_pos, points_[0], points_[3], points_[2]))
    {
        return true;
    }

    return false;

    /*
    auto A = 1; auto B = 2; auto C = 3; auto D = 0;

    wprintf(L"충돌 체크\n");
   
    auto AB = points_[B] - points_[A];
    auto BC = points_[C] - points_[B];
    
    auto dotABAB = (AB.X * AB.X) + (AB.Z * AB.Z);
    auto dotBCBC = (BC.X * BC.X) + (BC.Z * BC.Z);

    auto AM = other_pos - points_[A];
    auto BM = other_pos - points_[B];

    auto dotABAM = (AB.X * AM.X + AB.Z * AM.Z);
    auto dotBCBM = (BC.X * BM.X + BC.Z * BM.Z);

    if (dotABAM < 0.0f) return false;
    if (dotBCBM < 0.0f) return false;

    if (dotABAM > dotABAB) return false;
    if (dotABAM > dotBCBC) return false;
 
    wprintf(L"부딪혀서 터짐\n");
    return true;
    */
}

float collider::triangle_area(const vector3& a, const vector3& b, const vector3& c) const
{
    return fabs((a.X - c.X) * (b.Z - a.Z) - (a.X - b.X) * (c.Z - a.Z)) * 0.5f;
}
