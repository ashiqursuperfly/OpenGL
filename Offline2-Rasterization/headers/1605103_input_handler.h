//
// Created by ashiq on 5/16/21.
//

#ifndef OFFLINE2_1605103_INPUT_HANDLER_H
#define OFFLINE2_1605103_INPUT_HANDLER_H

#endif //OFFLINE2_1605103_INPUT_HANDLER_H

#include <fstream>
#include <stack>
#include <iomanip>


class InputHandler {
private:
    ofstream stage1, stage2, stage3;
    stack <Matrix> currentStack;
    stack <stack<Matrix>> history;
    Matrix VTM;
    Matrix PM;
public:

    InputHandler(const char *input_scene_file = "inputs/1/scene.txt") {
        FILE *fp;

        fp = freopen(input_scene_file, "r", stdin);

        if (fp == nullptr) {
            cout << "Error: No Input File Found" << endl;
            return ;
        }

        stage1.open("outputs/stage1.txt");
        stage2.open("outputs/stage2.txt");
        stage3.open("outputs/stage3.txt");
        stage1 << setprecision(7) << fixed;
        stage2 << setprecision(7) << fixed;
        stage3 << setprecision(7) << fixed;


        Vector eye, look, up;
        cin >> eye >> look >> up;
        double fovY, aspectRatio, near, far;
        cin >> fovY >> aspectRatio >> near >> far;

        VTM = Matrix::viewTransformation(eye, look, up);
        PM = Matrix::projection(near, far, fovY, aspectRatio);

        currentStack.push(Matrix::identity(4, 4));
    }

    void processInput() {

        string command;
        while (true) {
            cin >> command;

            if (command == "triangle") {
                processTriangle();
            } else if (command == "translate") {
                processTranslate();
            } else if (command == "scaling") {
                processScale();
            } else if (command == "rotate") {
                processRotate();
            } else if (command == "push") {
                history.push(currentStack);
            } else if (command == "pop") {
                currentStack = history.top();
                history.pop();
            } else if (command == "end") {
                break;
            }
        }

        stage1.close();
        stage2.close();
        stage3.close();
    }

    void processTriangle() {
        Vector points[3];
        cin >> points[0];
        cin >> points[1];
        cin >> points[2];

        for (const auto &p : points) {

            auto model = transformPoint(currentStack.top(), p);
            auto view = transformPoint(VTM, model);
            auto projection = transformPoint(PM, view);

            stage1 << model;
            stage2 << view;
            stage3 << projection;
        }

        stage1 << endl;
        stage2 << endl;
        stage3 << endl;
    }

    void processTranslate() {
        double dx, dy, dz;
        cin >> dx >> dy >> dz;

        auto t = Matrix::translation(dx, dy, dz);

        currentStack.push(currentStack.top() * t);
    }

    void processScale() {
        double sx, sy, sz;
        cin >> sx >> sy >> sz;

        auto t = Matrix::scaling(sx, sy, sz);

        currentStack.push(currentStack.top() * t);
    }

    void processRotate() {
        double angle;
        Vector axis;
        cin >> angle >> axis;

        axis = axis.normalize();

        auto col1 = rodrigues(Vector::I(), axis, angle);
        auto col2 = rodrigues(Vector::J(), axis, angle);
        auto col3 = rodrigues(Vector::K(), axis, angle);

        auto r = Matrix::rotation(col1, col2, col3);

        currentStack.push(currentStack.top() * r);
    }

    static Vector transformPoint(const Matrix &M, const Vector point) {

        auto result = (M * Matrix::column(point));
        return Vector(result.data[0][0], result.data[1][0], result.data[2][0]) / result.getW();
    }

    static Vector rodrigues(const Vector& x, const Vector& a, const double angle) {

        auto cost = cos(rad(angle));
        auto sint = sin(rad(angle));

        return x * cost  + a * ((1 - cost) * a.dot(x)) + (a * x) * sint;
    }

};