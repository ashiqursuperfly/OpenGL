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
    Vector direction;

    Bubble() {
        pos = Vector();
        direction = Vector(getRandomFloat() * 0.8f, getRandomFloat() * 0.8f, 0);
        radius = 5.00;
    }

    Bubble(const Vector &pos) {
        this -> pos = pos;
        direction = Vector(getRandomFloat() * 0.8f, getRandomFloat() * 0.8f, 0);
        radius = 5.00;
    }

};