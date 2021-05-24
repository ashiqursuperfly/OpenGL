//
// Created by ashiq on 5/24/21.
//

#ifndef OFFLINE2_1605103_ZBUFFER_H
#define OFFLINE2_1605103_ZBUFFER_H

#endif //OFFLINE2_1605103_ZBUFFER_H

#include "1605103_util.h"
#include "1605103_triangle.h"

class ZBufferExecutor{

    ofstream osZBuffer;
    double screenWidth, screenHeight;
    double xLimit, yLimit;
    double zRear, zFront;

public:

    ZBufferExecutor(const char *input_config_file = "inputs/1/config.txt") {
        FILE *fp = freopen(input_config_file, "r", stdin);

        if (fp == nullptr) {
            cout << "Error: Input File Not Found" << endl;
            return;
        }

        cin >> screenWidth >> screenHeight;
        cin >> xLimit;
        cin >> yLimit;

        xLimit = -xLimit;
        yLimit = -yLimit;

        cin >> zFront >> zRear;

        cout<<"SW:"<<screenWidth<<" SH:"<<screenHeight<<" xLim:"<<xLimit<<" yLim:"<<yLimit<<" zFront:"<<zFront<<" zRear:"<<zRear<<endl;

        osZBuffer.open("outputs/z-buffer.txt");

    }



};
