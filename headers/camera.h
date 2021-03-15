//
// Created by ashiq on 3/15/21.
//

#ifndef OFFLINE1_CAMERA_H
#define OFFLINE1_CAMERA_H

#endif //OFFLINE1_CAMERA_H

class Camera {
public:

    Vector pos;
    Vector u, r, l;

    Camera() {

        pos = Vector();
        pos.x = 150;
        pos.y = 150;
        pos.z = 50;

        u.x = 0;
        u.y = 0;
        u.z = 1;

        r.x = -1 / sqrt(2.0);
        r.y = 1 / sqrt(2.0);
        r.z = 0;

        l = u * r;

        print();
    }

    void print() const {
        std::cout<<"Pos:";
        pos.print();
        std::cout<<"l:";
        l.print();
        std::cout<<"r:";
        r.print();
        std::cout<<"u:";
        u.print();
    }
};