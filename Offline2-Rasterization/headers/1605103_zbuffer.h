//
// Created by ashiq on 5/24/21.
//

#ifndef OFFLINE2_1605103_ZBUFFER_H
#define OFFLINE2_1605103_ZBUFFER_H

#endif //OFFLINE2_1605103_ZBUFFER_H

#include "1605103_util.h"
#include "1605103_triangle.h"
#include "bitmap_image.hpp"

class ZBufferExecutor{

    std::ofstream osZBuffer;
    double screenWidth, screenHeight;
    double xLimit, yLimit;
    double zRear, zFront;
    double dx, dy;

    std::vector<Triangle> triangles;
    std::vector<std::vector<double>> zBuffer;
    std::vector<std::vector<Color>> pixelBuffer;

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

        dx = (xLimit - (-xLimit)) / screenWidth;
        dy = (yLimit - (-yLimit)) / screenHeight;


        std::cin >> zFront >> zRear;
        std::cout<<"SW:"<<screenWidth<<" SH:"<<screenHeight<<" xLim:"<<xLimit<<" yLim:"<<yLimit<<" zFront:"<<zFront<<" zRear:"<<zRear<<std::endl;
        std::cin.clear();

        osZBuffer.open("outputs/z-buffer.txt");
        osZBuffer << std::setprecision(7) << std::fixed;

        fp = freopen(input_triangles_file, "r", stdin);

        initBuffers();
        readTriangles();

    }

    void generateZBufferOutput() {
        for (auto & r: zBuffer) {
            for (auto & data: r) {
                if (data < zRear) {
                    osZBuffer<<data<<"    ";
                }
            }
            osZBuffer<<'\n';
        }

    }

    void generateImage() const {
        bitmap_image image((int)screenWidth, (int)screenHeight);

        for(int i=0;i<screenWidth;i++){
            for(int j=0;j<screenHeight;j++){
                auto color = getPixelBufferVal(i, j);
                image.set_pixel(j,i, color.r, color.g, color.b);
            }
        }
        image.save_image("outputs/out.bmp");
    }

    void initBuffers() {

        std::vector<double> rowZ((int)screenWidth, zRear);
        for (int i = 0; i < screenHeight; i++) {
            zBuffer.push_back(rowZ);
        }

        std::vector<Color> rowP((int)screenWidth, Color(0, 0, 0));
        for (int i = 0; i < screenHeight; i++) {
            pixelBuffer.push_back(rowP);
        }
    }

    double getZBufferVal(int row, int col) const {
        return zBuffer.at(row).at(col);
    }

    void setZBufferVal(int row, int col, double val) {
        zBuffer.at(row).at(col) = val;
    }

    Color getPixelBufferVal(int row, int col) const {
        return pixelBuffer.at(row).at(col);
    }

    void setPixelBufferVal(int row, int col, Color & c) {
        pixelBuffer.at(row).at(col) = c;
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

    }

    static std::vector<std::pair<Vector, Vector>> getIntersectingEdges(double yScanline, Triangle & t) {
        std::vector<std::pair<Vector, Vector>> result;

        if ((t.p1.y >= yScanline && t.p2.y <= yScanline)) {
            result.emplace_back(std::pair<Vector, Vector>(t.p1, t.p2));
        }
        else if (t.p1.y <= yScanline && t.p2.y >= yScanline) {
            result.emplace_back(std::pair<Vector, Vector>(t.p2, t.p1));
        }
        if (t.p2.y >= yScanline && t.p3.y <= yScanline) {
            result.emplace_back(std::pair<Vector, Vector>(t.p2, t.p3));
        }
        else if ((t.p2.y <= yScanline && t.p3.y >= yScanline)) {
            result.emplace_back(std::pair<Vector, Vector>(t.p3, t.p2));
        }
        if ((t.p1.y >= yScanline && t.p3.y <= yScanline)) {
            result.emplace_back(std::pair<Vector, Vector>(t.p1, t.p3));
        }
        else if (t.p1.y <= yScanline && t.p3.y >= yScanline) {
            result.emplace_back(std::pair<Vector, Vector>(t.p3, t.p1));
        }

        return result;
    }

    void applyProcedure() {
        for (auto t: triangles) {
            double yScanline = std::min(t.getMaxY(), yLimit); // - dy/2
            int topScanline = round((yLimit - yScanline) / dy);
            int bottomScanline = round((yLimit - std::max(t.getMinY(), -yLimit)) / dy);
            // std::cout<<"ts:"<<topScanline<<"bs:"<<bottomScanline<<std::endl;

            for (int row=topScanline; row < bottomScanline; row++) {
                auto edges = getIntersectingEdges(yScanline, t);

                if (edges.size() != 2) {
                    // std::cout<<"Apex Point "<<edges.size()<<std::endl;
                    yScanline -= dy;
                    continue;
                }

                auto p1 = edges.at(0);
                auto p2 = edges.at(1);

                double m1 = (yScanline - p1.first.y)/(p1.second.y - p1.first.y);
                double za = p1.first.z + m1 * (p1.second.z - p1.first.z);

                double m2 = (yScanline - p2.first.y)/(p2.second.y - p2.first.y);
                double zb = p2.first.z + m2 * (p2.second.z - p2.first.z);

                double xa = p1.first.x + m1 * (p1.second.x - p1.first.x);
                double xb = p2.first.x + m2 * (p2.second.x - p2.first.x);

                if (xb < xa) {
                    double temp = xa;
                    xa = xb;
                    xb = temp;

                    temp = za;
                    za = zb;
                    zb = temp;
                }

                xa = std::max(xa, -xLimit);
                xb = std::min(xb, xLimit);
                int leftIntersectingCol = round((xLimit + xa) / dx);
                int rightIntersectingCol = round((xLimit + xb) / dx);

                //std::cout<<"lic:"<<leftIntersectingCol<<"ric:"<<rightIntersectingCol<<std::endl;

                double m3 = (zb - za) / (xb - xa);
                double inc = dx * m3;
                double zp = za;
                for (int col = leftIntersectingCol; col < rightIntersectingCol; col++) {
                    if (zp > zFront && zp < getZBufferVal(row, col)) {
                        setZBufferVal(row, col, zp);
                        setPixelBufferVal(row, col, t.color);
                    }
                    zp = zp + inc;
                }
                yScanline -= dy;
            }

        }
    }

};
