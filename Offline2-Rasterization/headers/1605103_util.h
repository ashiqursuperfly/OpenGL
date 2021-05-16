//
// Created by ashiq on 5/16/21.
//

#ifndef OFFLINE2_1605103_UTIL_H
#define OFFLINE2_1605103_UTIL_H

#endif //OFFLINE2_1605103_UTIL_H

// dependencies for all headers
#include <random>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

#define rad(t) ((t) * pi / 180.0)
#define pi (2*acos(0.0))

float getRandomFloat() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    return (float)dist(mt);
}