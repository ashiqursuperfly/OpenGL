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
        pos.x = 35;
        pos.y = 25;
        pos.z = -60;

        u.x = 0.958635; // 0
        u.y = 0.167477; // 0
        u.z = 0.230155; // 1

        r.x = -0.225888; // -1 / sqrt(2.0);
        r.y = 0.939602; // 1 / sqrt(2.0);
        r.z = 0.257143; // 0;

        l = u * r;

        print();
    }

    void print() const {
//        std::cout<<"Pos:";
//        pos.print();
//        std::cout<<"l:";
//        l.print();
//        std::cout<<"r:";
//        r.print();
//        std::cout<<"u:";
//        u.print();
    }
};