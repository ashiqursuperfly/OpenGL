//
// Created by ashiq on 3/15/21.
//

#ifndef OFFLINE1_BUBBLE_H
#define OFFLINE1_BUBBLE_H

#endif //OFFLINE1_BUBBLE_H

enum BubbleState {
    OUTER, INNER
};

class Bubble {

public:
    BubbleState state;
    bool isVisible;
    float radius;
    Vector pos;
    Vector direction;

    static float MAX_SPEED;
    static float speed;

    Bubble() {
        pos = Vector();
        direction = Vector(getRandomFloat(), getRandomFloat(), 0).normalize();
        radius = 7.00;
        isVisible = false;
        state = OUTER;
    }

    Bubble(const Vector &pos) {
        this -> pos = pos;
        direction = Vector(getRandomFloat(), getRandomFloat(), 0).normalize();
        radius = 7.00;
        isVisible = false;
        state = OUTER;
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
