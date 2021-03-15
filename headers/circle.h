//
// Created by ashiq on 3/16/21.
//

#ifndef OFFLINE1_CIRCLE_H
#define OFFLINE1_CIRCLE_H

#endif //OFFLINE1_CIRCLE_H


class Circle {
public:
    Vector center;
    float radius;

    Circle() {}

    Circle(const Vector &center, float radius) : center(center), radius(radius) {}

    bool contains(Vector otherCenter) {

        double distance = center.getDistance(otherCenter);

        if (distance < radius) return true;

        return false;

    }
};