//
// Created by ashiq on 5/24/21.
//

#ifndef OFFLINE2_1605103_TRIANGLE_H
#define OFFLINE2_1605103_TRIANGLE_H

#endif //OFFLINE2_1605103_TRIANGLE_H

#include "1605103_color.h"

class Triangle {
public:
    Vector p1, p2, p3;
    Color color;

    Triangle(Vector& p1, Vector& p2, Vector& p3) {
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;

        this->color = Color((int)getRandomFloat(0, 255), (int)getRandomFloat(0, 255), (int)getRandomFloat(0, 255));
    }

    double getMaxX() const {
        double max = std::max(p1.x, p2.x);

        return std::max(max, p3.x);
    }

    double getMinX() const {
        double min = std::min(p1.x, p2.x);

        return std::min(min, p3.x);
    }

    double getMaxY() const {
        double max = std::max(p1.y, p2.y);

        return std::max(max, p3.y);
    }

    double getMinY() const {
        double min = std::min(p1.y, p2.y);

        return std::min(min, p3.y);
    }

    friend std::ostream &operator<<(std::ostream &os, const Triangle &t) {
        os <<"Points:(\n"<< t.p1 << t.p2 << t.p3 << ")\nColor" << t.color << std::endl;
        return os;
    }
};