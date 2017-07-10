#include "vector3.h"

//Constructors
vector3::vector3()
{
}

vector3::vector3(float const&x, float const&y, float const&z) : X(x), Y(y), Z(z) 
{
}

vector3 vector3::operator+(const vector3& vector) const
{
    return vector3(X + vector.X, Y + vector.Y, Z + vector.Z);
}

vector3 vector3::operator-(const vector3& vector) const
{
    return vector3(X - vector.X, Y - vector.Y, Z - vector.Z);
}

vector3 vector3::operator*(const vector3& vector) const
{
    return vector3(X * vector.X, Y * vector.Y, Z * vector.Z);
}

vector3 vector3::operator/(const vector3& vector) const
{
    return vector3(X / vector.X, Y / vector.Y, Z / vector.Z);
}

vector3& vector3::operator+=(const vector3& vector)
{
    X += vector.X;
    Y += vector.Y;
    Z += vector.Z;
    return *this;
}

vector3& vector3::operator-=(const vector3& vector)
{
    X -= vector.X;
    Y -= vector.Y;
    Z -= vector.Z;
    return *this;
}
vector3& vector3::operator*=(const vector3& vector)
{
    X *= vector.X;
    Y *= vector.Y;
    Z *= vector.Z;
    return *this;
}

vector3& vector3::operator/=(const vector3& vector)
{
    X /= vector.X;
    Y /= vector.Y;
    Z /= vector.Z;
    return *this;
}

 vector3 vector3::operator-() const
{
    return vector3(-X, -Y, -Z);
}

vector3 vector3::operator-(float const&num) const
{
    return vector3(X - num, Y - num, Z - num);
}

vector3 vector3::operator+(float const&num) const
{
    return vector3(X + num, Y + num, Z + num);
}

vector3 vector3::operator*(float const&num) const
{
    return vector3(X * num, Y * num, Z * num);
}

vector3 vector3::operator/(float const&num) const
{
    return vector3(X / num, Y / num, Z / num);
}

vector3& vector3::operator+=(const float& num)
{
    X += num;
    Y += num;
    Z += num;
    return *this;
}

vector3& vector3::operator-=(const float& num)
{
    X -= num;
    Y -= num;
    Z -= num;
    return *this;
}

vector3& vector3::operator*=(const float& num)
{
    X *= num;
    Y *= num;
    Z *= num;
    return *this;
}

vector3& vector3::operator/=(const float& num)
{
    X /= num;
    Y /= num;
    Z /= num;
    return *this;
}

bool vector3::operator==(const vector3& vector) const
{
    return X == vector.X && Y == vector.Y && Z == vector.Z;
}

bool vector3::operator!=(const vector3& vector) const
{
    return X != vector.X || Y != vector.Y || Z != vector.Z;
}



const vector3 vector3::Zero = vector3(0, 0, 0);
const vector3 vector3::Left(-1.f, 0.f, 0.f);
const vector3 vector3::Right(1.f, 0.f, 0.f);
const vector3 vector3::Up(0.f, 1.f, 0.f);
const vector3 vector3::Down(0.f, -1.f, 0.f);
const vector3 vector3::Forward(0.f, 0.f, 1.f);
const vector3 vector3::Backward(0.f, 0.f, -1.f);