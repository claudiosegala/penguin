#pragma once

#include <Point.h>
#include <iostream>

class Vec2 : public Point {
    public:

    Vec2(float xv = 0, float yv = 0);

    ///> Find magnitude of vector
    float GetLength() const;

    ///> Find angle with point (0, 0)
    float GetAngle() const;

    ///> Find angle between this vector and another
    float GetAngle(const Vec2&) const;

    ///> Transform vector, on unit
    void Unit();

    ///> Get unit vector
    Vec2 GetUnit() const;

    ///> Transform vector, rotating
    void Rotate(float);

    ///> Get rotated vector
    Vec2 GetRotate(float) const;
    
    ///> Cross product
    Vec2 operator* (const Vec2&);
    
    ///> Dot product
    float operator^ (const Vec2&) const;

    Vec2 operator* (const float) const;

    void operator*= (const float);

    Vec2 operator/ (const float) const;

    void operator/= (const float);

    Vec2 operator+(const Vec2&) const;

    Vec2 operator+= (const Vec2&);

    Vec2 operator-(const Vec2&) const;

    Vec2 operator-= (const Vec2&);

    Vec2 operator= (const Point&);

    Vec2 operator= (const Vec2&);

    friend std::ostream& operator<<(std::ostream &os, const  Vec2& n);

    friend std::istream& operator>>(std::istream &is, Vec2& n);
            
};