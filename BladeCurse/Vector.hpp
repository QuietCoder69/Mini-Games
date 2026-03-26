#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>
#include <float.h>
class Vector {
private:
    float x;
    float y;

public:
    // Constructor
    Vector(float x = 0, float y = 0) : x(x), y(y) {}

    // Convert given vector to integer (x)
    int Int_X() const { return static_cast<int>(x); }

    // Convert given vector to integer (y)
    int Int_Y() const { return static_cast<int>(y); }

    // Set the X value of vector to given number (float)
    void Set_X(float n) { x = n; }

    // Set the Y value of vector to given number (float)
    void Set_Y(float n) { y = n; }

    // Get the Y value
    float Get_Y() const { return y; }

    // Get the X value
    float Get_X() const { return x; }

    // Vector operations
    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }

    Vector operator+(const Vector& other) const {
        return Vector(x + other.x, y + other.y);
    }

    Vector operator*(float scalar) const {
        return Vector(x * scalar, y * scalar);
    }

    float length() const {
        return sqrt(x * x + y * y);
    }

    Vector normalize() const {
        float len = length();
        return Vector(x / len, y / len);
    }

    bool compare(const Vector& a , const Vector& b) const {
        return  (a.x == b.x && a.y == b.y) ? true : false; 
    }
     bool overlaps(const Vector& thispos,const Vector& otherPos, const Vector& otherDim, const Vector& thisDim) const {
        return !(
            otherPos.Get_X() > thispos.Get_X() + thisDim.Get_X() ||
            otherPos.Get_X() + otherDim.Get_X() < thispos.Get_X() ||
            otherPos.Get_Y() > thispos.Get_Y() + thisDim.Get_Y() ||
            otherPos.Get_Y() + otherDim.Get_Y() < thispos.Get_Y()
        );
    }

    float dot(const Vector& other) const {
        return x * other.x + y * other.y;
    }

    // Scale vector
    Vector scale(float scalar) const {
        return Vector(x * scalar, y * scalar);
    }

    // Subtract another vector
    Vector subtract(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }

};


#endif