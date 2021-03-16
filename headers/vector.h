//
// Created by ashiq on 3/15/21.
//

#ifndef OFFLINE1_VECTOR_H
#define OFFLINE1_VECTOR_H

#endif //OFFLINE1_VECTOR_H

#include <iostream>

#define pi (2*acos(0.0))

class Vector {
public:
    double x, y, z;

    Vector() {
        x = 0;
        y = 0;
        z = 0;
    }

    Vector(double x, double y, double z) : x(x), y(y), z(z) {}

    Vector operator+ (Vector const &rhs) const {

        Vector res;

        res.x = x + rhs.x;
        res.y = y + rhs.y;
        res.z = z + rhs.z;

        return res;
    }

    Vector operator- (Vector const &rhs) const {

        Vector res;

        res.x = x - rhs.x;
        res.y = y - rhs.y;
        res.z = z - rhs.z;

        return res;
    }

    Vector operator- () const {

        Vector res;

        res.x = -x;
        res.y = -y;
        res.z = -z;

        return res;
    }

    Vector operator* (Vector const & rhs) const {

        Vector res;

        res.x = y * rhs.z - z * rhs.y;
        res.y = z * rhs.x - x * rhs.z;
        res.z = x * rhs.y - y * rhs.x;

        return res;

    }

    Vector operator* (double scalar) const {

        Vector res;

        if (scalar != 0) {
            res.x = x * scalar;
            res.y = y * scalar;
            res.z = z * scalar;
        }

        return res;
    }

    double getDistance(Vector const & rhs) const {

        double dX = x - rhs.x;
        double dY = y - rhs.y;
        double dZ = z - rhs.z;

        return sqrt(dX * dX + dY * dY + dZ * dZ);

    }

    double dot(Vector const & rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    Vector normalize() const {

        Vector res;

        float val = sqrt(x * x + y * y + z * z);

        res.x = x / val;
        res.y = y / val;
        res.z = z / val;

        return res;
    }

    Vector rotate(Vector const & axis, double angleDegrees) const {
        //qr this vector with respect to an axis
        Vector crossProduct = axis * (*this);

        // r1 = lxCost , lyCost
        // r2 = rxSint , rySint
        // res = (lxCost + rxSint) , (lyCost + rySint)

        Vector r1 = (*this) * cos(angleDegrees * pi / 180);
        Vector r2 = crossProduct * sin(angleDegrees * pi / 180.0);

        return r1 + r2;
    }

    void print() const {
        std::cout<<"( "<<x<<","<<y<<","<<z<<" )"<<std::endl;
    }
};