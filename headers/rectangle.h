//
// Created by ashiq on 3/15/21.
//

#ifndef OFFLINE1_RECTANGLE_H
#define OFFLINE1_RECTANGLE_H

#endif //OFFLINE1_RECTANGLE_H


enum RectCollision {
    NO_COLLISION, L_R_WALL, T_B_WALL
};

class Rectangle {
public:
    Vector tl, tr, bl, br;

    Rectangle() {}

    Rectangle(const Vector &tl, const Vector &tr, const Vector &bl, const Vector &br) : tl(tl), tr(tr), bl(bl), br(br) {}

    RectCollision contains(Vector & p) {

        double maxX = std::max(tl.x, tr.x);
        maxX = std::max(maxX, bl.x);
        maxX = std::max(maxX, br.x);

        double minX = std::min(tl.x, tr.x);
        minX = std::min(minX, bl.x);
        minX = std::min(minX, br.x);

        double maxY = std::max(tl.y, tr.y);
        maxY = std::max(maxY, bl.y);
        maxY = std::max(maxY, br.y);

        double minY = std::min(tl.y, tr.y);
        minY = std::min(minY, bl.y);
        minY = std::min(minY, br.y);

        if (p.x < minX || p.x > maxX) return L_R_WALL;
        if (p.y < minY || p.y > maxY) return T_B_WALL;

        return NO_COLLISION;

    }

};