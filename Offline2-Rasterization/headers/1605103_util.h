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
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>

using namespace std;

#define rad(t) ((t) * pi / 180.0)
#define pi (2*acos(0.0))

bool compareFiles(const std::string& p1, const std::string& p2) {
    std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

    if (f1.fail() || f2.fail()) {
        return false; //file problem
    }

//    if (f1.tellg() != f2.tellg()) {
//        return false; //size mismatch
//    }

    //seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                      std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf()));
}

float getRandomFloat() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    return (float)dist(mt);
}