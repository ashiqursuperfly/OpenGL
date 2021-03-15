//
// Created by ashiq on 3/15/21.
//

#ifndef OFFLINE1_BUBBLE_H
#define OFFLINE1_BUBBLE_H

#endif //OFFLINE1_BUBBLE_H

class Bubble {
public:
    bool isVisible;
    float radius;
    Vector pos;
    Vector direction;

    Bubble() {
        pos = Vector();
        direction = Vector(getRandomDirection(), getRandomDirection(), 0);
        radius = 5.00;
        isVisible = false;
    }

    Bubble(const Vector &pos) {
        this -> pos = pos;
        direction = Vector(getRandomDirection(), getRandomDirection(), 0);
        radius = 5.00;
        isVisible = false;
    }

};