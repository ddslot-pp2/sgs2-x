#include "collider.h"
#define _USE_MATH_DEFINES 
#include <cmath>  

collider::collider(const vector3& pos, const vector3& size) : pos_(pos), size_(size)
{
    
}

bool collider::check_intersection(const vector3& other_pos, const vector3& other_size) const
{
    auto rotate_point = [](float cx, float cz, float degree, vector3 p) {
        auto angle = degree * (3.14159f / 180.0f) * -1.0f;

        return vector3(
            cos(angle) * (p.X - cx) - sin(angle) * (p.Z - cz) + cx,
            0.0f,
            sin(angle) * (p.X - cx) + cos(angle) * (p.Z - cz) + cz
        );
    };

    vector3 points[4] = {};
    points[0] = vector3(pos_.X + (size_.X / 2.0f), 0.0f, pos_.Z + (size_.Z / 2.0f));
    points[1] = vector3(pos_.X + (size_.X / 2.0f), 0.0f, pos_.Z - (size_.Z / 2.0f));
    points[2] = vector3(pos_.X - (size_.X / 2.0f), 0.0f, pos_.Z - (size_.Z / 2.0f));
    points[3] = vector3(pos_.X - (size_.X / 2.0f), 0.0f, pos_.Z + (size_.Z / 2.0f));

    for (auto i = 0; i < 4; ++i)
    {
        auto rot_point = rotate_point(pos_.X, pos_.Z, -45.0f, points[i]);
        //auto rot_point = rotate_point(pos_.X, pos_.Z, -16.873f, points[i]);
        //wprintf(L"before x: %f, z: %f\n", points[i].X, points[i].Z);
        wprintf(L"after  x: %f, z: %f\n", rot_point.X, rot_point.Z);
        points[i] = rot_point;
    }

    auto A = points[0];
    auto B = points[1];
    auto C = points[2];
    auto D = points[3];

    //return true;

    wprintf(L"---------------------------------\n");
    auto rect_area = size_.X * size_.Z;
    wprintf(L"Rect area: %f\n", rect_area);
    wprintf(L"---------------------------------\n");

    auto triangle_area = [](vector3 A, vector3 B, vector3 C)
    {
        auto area = fabs((A.X - C.X) * (B.Z - A.Z) - (A.X - B.X) * (C.Z - A.Z)) / 2;
        return area;
    };

    /*
    auto triangle_area = [](vector3 A, vector3 B, vector3 C)
    {
        return abs((B.X * A.Z - A.X * B.Z) + (C.X * B.X - B.X * C.X) + (A.X * C.Z - C.X * A.Z)) / 2.0f;
    };
    */

    //vector3 P(10.0f, 0.0f, 0.0f);
    vector3 P = other_pos;

    auto triarea_0 = triangle_area(A, P, D);
    auto triarea_1 = triangle_area(D, P, C);
    auto triarea_2 = triangle_area(C, P, B);
    auto triarea_3 = triangle_area(P, B, A);

    wprintf(L"Triangle area 0: %f\n", triarea_0);
    wprintf(L"Triangle area 1: %f\n", triarea_1);
    wprintf(L"Triangle area 2: %f\n", triarea_2);
    wprintf(L"Triangle area 3: %f\n", triarea_3);

  
    wprintf(L"총알의 위치=> x: %f, z: %f", P.X, P.Z);

    if (rect_area < (triarea_0 + triarea_1 + triarea_2 + triarea_3))
    {
        wprintf(L"점이 사각형 안에 없음\n");
        return false;
    }
  
    wprintf(L"점이 사각형 안에 있음\n");
    //auto bullet_pos = other_pos;



    return true;
}

/*
bool collider::check_intersection(const vector3& other_pos, const vector3& other_size) const
{

    auto rotate_point = [](float cx, float cz, float degree, vector3 p) {
        auto angle = degree * (3.14159f / 180.0f) * -1.0f;

        return vector3(
            cos(angle) * (p.X - cx) - sin(angle) * (p.Z - cz) + cx,
            0.0f,
            sin(angle) * (p.X - cx) + cos(angle) * (p.Z - cz) + cz
        );
    };

    vector3 points[4] = {};
    points[0] = vector3(other_pos.X + (other_size.X / 2.0f), 0.0f, other_pos.Z + (other_size.Z / 2.0f));
    points[1] = vector3(other_pos.X + (other_size.X / 2.0f), 0.0f, other_pos.Z - (other_size.Z / 2.0f));
    points[2] = vector3(other_pos.X - (other_size.X / 2.0f), 0.0f, other_pos.Z - (other_size.Z / 2.0f));
    points[3] = vector3(other_pos.X - (other_size.X / 2.0f), 0.0f, other_pos.Z + (other_size.Z / 2.0f));

    const auto half_x = (size_.X / 2.0f);
    const auto half_z = (size_.Z / 2.0f);

    auto a_min_x = pos_.X - half_x;
    auto a_max_x = pos_.X + half_x;
    auto a_min_z = pos_.Z - half_z;
    auto a_max_z = pos_.Z + half_z;

    for (auto i = 0; i < 4; ++i)
    {
        auto rotated_point = rotate_point(other_pos.X, other_pos.Z, -16.873f, points[i]);

        if (rotated_point.X > a_min_x && rotated_point.X < a_max_x &&
            rotated_point.Z > a_min_z && rotated_point.Z < a_max_z)
        {
            return true;
        }
    }

    //wprintf(L"rx: %f, rz: %f\n", points[0].X, points[0].Z);

    return false;
}
*/

/*
const auto half_x = (size_.X / 2.0f);
const auto half_z = (size_.Z / 2.0f);

const auto other_half_x = (other_size.X / 2.0f);
const auto other_half_z = (other_size.Z / 2.0f);

//printf("enemy => x: %f, y: %f, z: %f\n", object_pos.X, object_pos.Y, object_pos.Z);
auto a_min_x = pos_.X - half_x;
auto a_max_x = pos_.X + half_x;
auto a_min_z = pos_.Z - half_z;
auto a_max_z = pos_.Z + half_z;

auto b_min_x = other_pos.X - other_half_x;
auto b_max_x = other_pos.X + other_half_x;
auto b_min_z = other_pos.Z - other_half_z;
auto b_max_z = other_pos.Z + other_half_z;


if (a_max_x < b_min_x || a_min_x > b_max_x) return false;
if (a_max_z < b_min_z || a_min_z > b_max_z) return false;

return true;
*/