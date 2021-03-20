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

    bool contains(Vector & otherCenter, float offset) {

        double distance = center.getDistance(otherCenter);

        if (distance < radius - offset) return true;

        return false;

    }

    void draw() {
        glColor3f(1.0, 0, 0);
        drawCircleXY(radius, 50, center);
    }

};