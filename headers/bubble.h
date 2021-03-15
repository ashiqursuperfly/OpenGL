//
// Created by ashiq on 3/15/21.
//

#ifndef OFFLINE1_BUBBLE_H
#define OFFLINE1_BUBBLE_H

#endif //OFFLINE1_BUBBLE_H

class Bubble {
public:
    float radius;
    Vector pos;
    Vector speed;

    Bubble() {
        pos = Vector();
        speed = Vector(getRandomFloat() * 0.2f, getRandomFloat() * 0.2f, 0);
        radius = 5.00;
    }

    Bubble(const Vector &pos) {
        this -> pos = pos;
        speed = Vector(getRandomFloat() * 0.2f, getRandomFloat() * 0.2f, 0);
        radius = 5.00;
    }

};