//
// Created by ashiq on 3/15/21.
//

#ifndef OFFLINE1_RECTANGLE_H
#define OFFLINE1_RECTANGLE_H

#endif //OFFLINE1_RECTANGLE_H


class Rectangle {
public:
    Vector tl, tr, bl, br;

    Rectangle() {}

    Rectangle(const Vector &tl, const Vector &tr, const Vector &bl, const Vector &br) : tl(tl), tr(tr), bl(bl), br(br) {}

    bool contains(Vector & p) {

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

        if (p.x < maxX && p.x > minX && p.y < maxY && p.y > minY) return true;

        return false;

    }

};