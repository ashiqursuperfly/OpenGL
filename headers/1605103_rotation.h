//
// Created by ashiq on 3/20/21.
//

#ifndef OFFLINE1_ROTATION_H
#define OFFLINE1_ROTATION_H

#endif //OFFLINE1_ROTATION_H

class Rotation {
public:
    Vector axis;
    float angleDegrees;
    float maxAngle;

    Rotation(const Vector &axis, float angleDegrees, float maxAngle) : axis(axis), angleDegrees(angleDegrees), maxAngle(maxAngle) {}

    bool updateAngle(float del) {
        if (std::abs(angleDegrees + del) < maxAngle) {
            angleDegrees += del;
            return true;
        }
        return false;
    }
};