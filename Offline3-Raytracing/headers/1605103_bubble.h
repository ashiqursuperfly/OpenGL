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

    static void updateSpeed(float delta) {

        float temp = Bubble::speed + delta;

        if (temp < MAX_SPEED) {
            if (temp > 0) {
                Bubble::speed = temp;
            }
            else Bubble::speed = 0;
        }

        else Bubble::speed = MAX_SPEED;
        std::cout<<"Speed:"<<speed<<std::endl;
    }

    bool checkCollision(Bubble & rhs){

        double dist = pos.getDistance(rhs.pos);
        if (dist >= rhs.radius + radius - radius/2.5 && dist <= rhs.radius + radius + radius/2.5) {
            return true;
        }
        else if (dist <= (rhs.radius + radius)/1.5) {
            rhs.pos = rhs.pos + rhs.direction * Bubble::speed * rhs.radius;
        }
        return false;

    }

    void print() const {
        std::cout<<"Pos:";
        pos.print();
        std::cout<<"Dir:";
        direction.print();
    }

    void draw() {
        if (isVisible) {
            glColor3f(1.0, 1.0, 1.0);
            drawCircleXY(radius, 50, pos);
        }
    }
};

float Bubble::MAX_SPEED = 0.3;
float Bubble::speed = 0.1;

