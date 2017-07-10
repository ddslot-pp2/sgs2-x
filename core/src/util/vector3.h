/*
* Vector3.h
*
*  Created on: Dec 4, 2011
*      Author: kyle J
*/

#ifndef VECTOR3_H_
#define VECTOR3_H_
#include <ostream>
#include <sstream>
#include <cmath>
#include <cfloat>
//#include "const.h"

class vector3
{
public:
	//Members
	float X;
	float Y;
	float Z;
	//Constructors
    vector3();
	explicit vector3(float const&x, float const&y, float const&z);
	//Vector3 by Vector3 Math
    vector3		operator+(const vector3& vector) const;
    vector3		operator-(const vector3& vector) const;
    vector3		operator*(const vector3& vector) const;
    vector3		operator/(const vector3& vector) const;
    vector3&	operator+=(const vector3& vector);
    vector3&	operator-=(const vector3& vector);
    vector3&	operator*=(const vector3& vector);
    vector3&	operator/=(const vector3& vector);
	//Vector3 by Float Math
    vector3		operator-() const;
    vector3		operator+(float const&num) const;
    vector3		operator-(float const&num) const;
    vector3		operator*(float const&num) const;
    vector3		operator/(float const&num) const;
    vector3&	operator+=(float const&num);
    vector3&	operator-=(float const&num);
    vector3&	operator*=(float const&num);
    vector3&	operator/=(float const&num);
	//Boolean Equals Operators
	bool		operator==(const vector3& vector) const;
	bool		operator!=(const vector3& vector) const;
	//Static Predefines
	static const vector3 Zero;
	static const vector3 Left;
	static const vector3 Right;
	static const vector3 Up;
	static const vector3 Down;
	static const vector3 Forward;
	static const vector3 Backward;
	/*TODO:
	Vector3	UnitCross(const Vector3& vec1, const Vector3& vec2);
	static void Orthonormalize (Vector3& rkU, Vector3& rkV,	Vector3& rkW);
	static void Orthonormalize (Vector3* akV);
	static void GenerateOrthonormalBasis (Vector3& rkU,	Vector3& rkV, Vector3& rkW, bool bUnitLengthW);
	Vector4 toVec4
	Quanternion ToQuat

	*/
	//Print out
	friend std::ostream& operator<< (std::ostream& ofs, const vector3& vector);
};




//-----------------------------------------------------------------------------------
//Fast Static members
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
//Fast non-member functions
//-----------------------------------------------------------------------------

//Returns (Float) dot product of the two Vector3 objects
inline float dot(vector3 const&vec1, vector3 const&vec2) {
    return vec2.X*vec1.X + vec2.Y*vec1.Y + vec2.Z*vec1.Z;
}
//Returns (Float) length squared of the Vector3 object
inline float lengthSquared(vector3 const&vector) {
    return dot(vector, vector);
}
//Returns (Float) magnitude (length) of the Vector3 object
inline float magnitude(vector3 const &vector) {
    return sqrt(dot(vector, vector));
}
//Returns (Float) distance squared between the two Vector3 objects
inline float distanceSquared(vector3 const&vec1, vector3 const&vec2) {
    auto ySeparation = vec1.Y - vec2.Y;
    auto xSeparation = vec1.X - vec2.X;
    auto zSeparation = vec1.Z - vec2.Z;
    return (float)ySeparation*ySeparation + xSeparation*xSeparation + zSeparation*zSeparation;
}
//Returns (Float) distance between the two Vector3 objects
inline float distance(vector3 const&vec1, vector3 const&vec2) {
    auto ySeparation = vec1.Y - vec2.Y;
    auto xSeparation = vec1.X - vec2.X;
    auto zSeparation = vec1.Z - vec2.Z;
    return sqrtf(ySeparation*ySeparation + xSeparation*xSeparation + zSeparation*zSeparation);
}



//Voids
inline void setMagnitude(vector3& vec2, float const&num)
{
    vec2 *= num / magnitude(vec2);
}
//Sets
inline void setLengthSquared(vector3& vector, float const&num)
{
    float vecLength = lengthSquared(vector);

    if (vecLength == 0)
    {
        return;
    }

    vector *= num / sqrt(vecLength);
}
//Returns a normalized Vector3 of the Vector3 object
inline vector3 normalize(vector3 const &vector) {
    return vector * (1.f / (magnitude(vector) + FLT_MIN));
}
inline void toNormalized(vector3 &vector) {
    vector *= (1.f / (magnitude(vector) + FLT_MIN));
}
inline void toPolar(vector3 &vector, float const&x, float const&y, float const&z)
{
    vector = vector3(
        atan2(y, x),
        sqrt(x * x + y * y),
        z);
}

inline void toCartesian(vector3 &vector, float const&radius, float const&angle, float const&z)
{
    vector = vector3(
        radius * cos(angle),
        radius * sin(angle),
        z);
}
inline void toEuler(vector3 &vector, vector3 axis, float const& angle)
{
    vector3 out = vector3();

    float s = sin(angle);
    float c = cos(angle);
    float t = static_cast<float>(1.0) - c;

    if ((axis.X * axis.Y * t + axis.Z * s) > static_cast<float>(0.998))// north pole singularity detected
    {
        out.Y = static_cast<float>(2.0) * atan2(axis.X * sin(angle / static_cast<float>(2.0)), cos(angle / static_cast<float>(2.0)));
        out.Z = static_cast<float>(1.57079633);//PI/2
        out.X = 0;
        vector = out;
        return;
    }
    if ((axis.X * axis.Y * t + axis.Z * s) < static_cast<float>(-0.998))// south pole singularity detected
    {
        out.Y = static_cast<float>(-2.0) * atan2(axis.X * sin(angle / static_cast<float>(2.0)), cos(angle / static_cast<float>(2.0)));
        out.Z = -static_cast<float>(1.57079633);//PI/2
        out.X = 0;
        vector = out;
        return;
    }
    out.Y = atan2(axis.Y * s - axis.X * axis.Z * t, 1 - (axis.Y * axis.Y + axis.Z * axis.Z) * t);
    out.Z = asin(axis.X * axis.Y * t + axis.Z * s);
    out.X = atan2(axis.X * s - axis.Y * axis.Z * t, 1 - (axis.X * axis.X + axis.Z * axis.Z) * t);
    vector = out;
}
//Returns (Vector3) cross product of the Vector3 objects
inline vector3 cross(vector3 const &vec2, vector3 const &vec1) {
    return vector3(
        vec2.Y * vec1.Z - vec1.Y * vec2.Z,
        -(vec2.X * vec1.Z - vec1.X * vec2.Z),
        vec2.X * vec1.Y - vec1.X * vec2.Y);
}
//Returns (Vector3) a perpendicular Vector3 of the Vector3 object
inline const vector3 perpendicular(vector3 const &vector) {
    return vector3(-vector.Z, vector.X, -vector.Y);//right
}

//Clamps (Vector3) values of the Vector3 object to max
inline void truncate(vector3 &vector, float const& max) {
    if (magnitude(vector) > max)
    {
        toNormalized(vector);
        vector *= max;
    }
}
//Sets (Vector3) values of the Vector3 object to zero
inline void toZero(vector3 &vec2) {
    vec2.X = 0.0f;
    vec2.Y = 0.0f;
    vec2.Z = 0.0f;
}
//Returns (Boolean) True if the Vector3 object is zero else False
inline const bool isZero(vector3 const&vector) {
    return (vector.X*vector.X + vector.Y*vector.Y + vector.Z*vector.Z)<(float)0.000001;//EPSILON
}
//TODO:Returns negative or positive (value of one)
inline const int sign(const vector3& vec1, const vector3& vec2) {
    if (vec2.Y*vec1.X > vec2.X*vec1.Y)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
//Returns (Vector3) inverse (negative) of the Vector3 object
inline vector3 negate(vector3 const &vec1) {
    return vector3(-vec1.X, -vec1.Y, -vec1.Z);
}


//Returns (Vector3) of vec1 "Assumed Velocity" reflected over the vec2 "Assumed Normal"  object
inline vector3 reflect(vector3 const& vec1, const vector3& vec2)
{
    vector3 out;
    const float dotProductTimesTwo = dot(vec2, vec1) * 2.0f;
    out.X = vec2.X - (dotProductTimesTwo * vec1.X);
    out.Y = vec2.Y - (dotProductTimesTwo * vec1.Y);
    out.Z = vec2.Z - (dotProductTimesTwo * vec1.Z);
    return out;
}
//Returns (Vector3) of vec1 linearly interpolated to vec2 with the percent of num
inline vector3 lerp(vector3 const&vec1, vector3 const&vec2, float const& num)
{
    return (vec1 + ((vec2 - vec1)*num));
}
//TODO: Clamp value
//Returns (Vector3) of vec1 Spherically interpolated to vec2 with the percent of num
inline vector3 slerp(vector3 const& vec1, vector3 const&vec2, float const& num)
{
    float doot = dot(vec1, vec2);
    //math.clamp(doot, -1,1);
    float theta = acos(doot)*num;
    vector3 RelativeVec = vec2 - vec1*doot;
    toNormalized(RelativeVec);
    return ((vec1*cos(theta)) + (RelativeVec*sin(theta)));
}
//Returns (Vector3) of "Normalized" vec1 interpolated to vec2 with the percent of num
inline vector3 nlerp(vector3 const& vec1, vector3 const&vec2, float const& num)
{
    return normalize(lerp(vec1, vec2, num));
}

//Output display of values
inline std::ostream& operator<< (std::ostream& os, const vector3& vector)
{
    std::stringstream stream;
    stream << "X: " << vector.X << ", Y: " << vector.Y << ", Z: " << vector.Z;
    os.write(const_cast<char*>(stream.str().c_str()), static_cast<std::streamsize>(stream.str().size() * sizeof(char)));
    return os;
}



#endif /* VECTOR3_H_ */
