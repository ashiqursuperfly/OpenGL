//
// Created by ashiq on 5/24/21.
//

#ifndef OFFLINE2_1605103_ZBUFFER_H
#define OFFLINE2_1605103_ZBUFFER_H

#endif //OFFLINE2_1605103_ZBUFFER_H

#include "1605103_util.h"
#include "1605103_triangle.h"

class ZBufferExecutor{

    std::ofstream osZBuffer;
    double screenWidth, screenHeight;
    double xLimit, yLimit;
    double zRear, zFront;

    std::vector<Triangle> triangles;

public:

    ZBufferExecutor(const char *input_config_file = "inputs/1/config.txt", const char *input_triangles_file = "inputs/1/stage3.txt") {
        FILE *fp = freopen(input_config_file, "r", stdin);

        if (fp == nullptr) {
            std::cout << "Error: Input File Not Found" << std::endl;
            return;
        }

        std::cin >> screenWidth >> screenHeight;
        std::cin >> xLimit;
        std::cin >> yLimit;

        xLimit = -xLimit;
        yLimit = -yLimit;

        std::cin >> zFront >> zRear;
        std::cout<<"SW:"<<screenWidth<<" SH:"<<screenHeight<<" xLim:"<<xLimit<<" yLim:"<<yLimit<<" zFront:"<<zFront<<" zRear:"<<zRear<<std::endl;
        std::cin.clear();

        osZBuffer.open("outputs/z-buffer.txt");

        fp = freopen(input_triangles_file, "r", stdin);

        readTriangles();

    }

    void readTriangles() {

        int i = 0;
        while (true) {
            Vector p1, p2, p3;

            std::cin >> p1;
            if (std::cin.eof()) break;
            std::cin >> p2;
            if (std::cin.eof()) break;
            std::cin >> p3;
            triangles.emplace_back(p1, p2, p3);

            if (std::cin.eof()) {break;}

        }

        std::cout<<"Triangles Found: "<<triangles.size()<<std::endl;

        std::cout<<triangles.at(0)<<std::endl;

    }


};
