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
        pos.x = 0;
        pos.y = 0;
        pos.z = 200;

        l.x = 0;
        l.y =  0;
        l.z =  -1;

        r.x = -1 / sqrt(2.0);
        r.y = 1 / sqrt(2.0);
        r.z = 0;

        u = l * r;

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