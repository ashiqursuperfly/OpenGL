//
// Created by ashiq on 5/16/21.
//

#ifndef OFFLINE2_1605103_INPUT_HANDLER_H
#define OFFLINE2_1605103_INPUT_HANDLER_H

#endif //OFFLINE2_1605103_INPUT_HANDLER_H

#include "1605103_vector.h"
#include "1605103_matrix.h"
#include <fstream>
#include <stack>
#include <iomanip>
#include <string>

class InputHandler {
private:
    std::ofstream osStage1, osStage2, osStage3;
    std::stack <Matrix> currentStack;
    std::stack <std::stack<Matrix>> history;
    Matrix VTM;
    Matrix PM;
public:

    InputHandler(const char *input_scene_file = "inputs/1/scene.txt") {

        FILE *fp = freopen(input_scene_file, "r", stdin);

        if (fp == nullptr) {
            std::cout << "Error: Input File Not Found" << std::endl;
            return;
        }

        osStage1.open("outputs/stage1.txt");
        osStage2.open("outputs/stage2.txt");
        osStage3.open("outputs/stage3.txt");
        osStage1 << std::setprecision(7) << std::fixed; osStage2 << std::setprecision(7) << std::fixed; osStage3 << std::setprecision(7) << std::fixed;

        Vector eye, look, up;
        std::cin >> eye >> look >> up;
        double fovY, aspectRatio, near, far;
        std::cin >> fovY >> aspectRatio >> near >> far;

        std::cout<<"Eye:"<<eye<<std::endl;
        std::cout<<"Look:"<<look<<std::endl;
        std::cout<<"Up:"<<up<<std::endl;
        std::cout<<"fovY: "<<fovY<<" aspectRatio: "<<aspectRatio<<" near: "<<near<<" far: "<<far<<std::endl;

        VTM = Matrix::viewTransformation(eye, look, up);
        PM = Matrix::projection(near, far, fovY, aspectRatio);

        currentStack.push(Matrix::identity(4, 4));
    }

    void processInput() {

        std::string instruction;
        while (true) {
            std::cin >> instruction;

            if (instruction == "triangle") {
                processTriangle();
            } else if (instruction == "translate") {
                processTranslate();
            } else if (instruction == "scale") {
                processScale();
            } else if (instruction == "rotate") {
                processRotate();
            } else if (instruction == "push") {
                history.push(currentStack);
            } else if (instruction == "pop") {
                currentStack = history.top();
                history.pop();
            } else if (instruction == "end") {
                std::cin.clear();
                break;
            }
        }

        osStage1.close();
        osStage2.close();
        osStage3.close();
    }

    void processTriangle() {
        Vector points[3];
        std::cin >> points[0];
        std::cin >> points[1];
        std::cin >> points[2];

        for (int i=0; i < 3; i++) {

            auto model = transformPoint(points[i], currentStack.top());
            auto view = transformPoint(model, VTM);
            auto projection = transformPoint(view, PM);

            osStage1 << model; osStage2 << view; osStage3 << projection;
        }

        osStage1 << std::endl; osStage2 << std::endl; osStage3 << std::endl;
    }

    void processTranslate() {
        double dx, dy, dz;
        std::cin >> dx >> dy >> dz;

        auto t = Matrix::translation(dx, dy, dz);

        currentStack.push(currentStack.top() * t);
    }

    void processScale() {
        double sx, sy, sz;
        std::cin >> sx >> sy >> sz;

        auto t = Matrix::scaling(sx, sy, sz);

        currentStack.push(currentStack.top() * t);
    }

    void processRotate() {
        double angle;
        Vector axis;
        std::cin >> angle >> axis;

        axis = axis.normalize();

        auto col1 = rodrigues(Vector::I(), axis, angle);
        auto col2 = rodrigues(Vector::J(), axis, angle);
        auto col3 = rodrigues(Vector::K(), axis, angle);

        auto r = Matrix::rotation(col1, col2, col3);

        currentStack.push(currentStack.top() * r);
    }

    static Vector transformPoint(const Vector point, const Matrix &T) {

        auto res = T * Matrix::column(point);
        return Vector(res.data[0][0], res.data[1][0], res.data[2][0]) / res.getW();
    }

    static Vector rodrigues(const Vector& x, const Vector& a, const double angle) {

        auto cost = cos(rad(angle));
        auto sint = sin(rad(angle));

        return x * cost  + a * ((1 - cost) * a.dot(x)) + (a * x) * sint;
    }
};