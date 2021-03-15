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

    static float MAX_SPEED;
    static float speed;

    Bubble() {
        pos = Vector();
        direction = Vector(getRandomDirection(), getRandomDirection(), 0).normalize();
        radius = 5.00;
        isVisible = false;
    }

    Bubble(const Vector &pos) {
        this -> pos = pos;
        direction = Vector(getRandomDirection(), getRandomDirection(), 0).normalize();
        radius = 5.00;
        isVisible = false;
    }

    static void updateSpeed(float delta) {

        float temp = Bubble::speed + delta;

        if (temp < MAX_SPEED) {
            if (temp > 0) {
                Bubble::speed = temp;
            }
            else Bubble::speed = 0;
        }

        else Bubble::speed = MAX_SPEED;
    }

    void print() {
        std::cout<<"Pos:";
        pos.print();
        std::cout<<"Dir:";
        direction.print();
    }

};

float Bubble::MAX_SPEED = 1.0;
float Bubble::speed = 0.2;
