//
// Created by ashiq on 5/15/21.
//

#ifndef OFFLINE2_1605103_MATRIX_H
#define OFFLINE2_1605103_MATRIX_H

#endif //OFFLINE2_1605103_MATRIX_H

#include <vector>
#include <iostream>

class Matrix {

public:
    std::vector<std::vector<double>> data;

    Matrix() = default;

    Matrix(const Matrix &m) {
        this->data = m.data;
    }

    Matrix(int r, int c) {
        std::vector<double> row(c, 0);
        for (int i = 0; i < r; i++) {
            data.push_back(row);
        }
    }

    double getW() {
        return data[data.size() - 1][data[0].size() - 1];
    }

    void setW(double val) {
        data[data.size() - 1][data[0].size() - 1] = val;
    }

    static Matrix zero(int r, int c) {
        return Matrix(r, c);
    }

    static Matrix identity(int r = 4, int c = 4) {
        auto res = zero(r, c);
        for (int i = 0; i < res.data.size(); i++) {
            res.data[i][i] = 1;
        }
        return res;
    }

    static Matrix column(const Vector &Vector) {
        auto res = zero(4, 1);

        res.data[0][0] = Vector.x;
        res.data[1][0] = Vector.y;
        res.data[2][0] = Vector.z;
        res.data[3][0] = 1;
        return res;
    }

    static Matrix translation(double dx, double dy, double dz) {
        auto res = identity(4, 4);
        res.data[0][3] = dx; res.data[1][3] = dy; res.data[2][3] = dz;
        return res;
    }

    static Matrix scaling(double sx, double sy, double sz) {
        auto res = zero(4, 4);
        res.data[0][0] = sx; res.data[1][1] = sy; res.data[2][2] = sz;
        res.setW(1);

        return res;
    }

    static Matrix rotation(Vector col0, Vector col1, Vector col2) {

        auto res = zero(4, 4);

        std::vector<Vector> columns;
        columns.push_back(col0);
        columns.push_back(col1);
        columns.push_back(col2);

        for (int col = 0; col < 3; col++) {
            res.data[0][col] = columns[col].x;
            res.data[1][col] = columns[col].y;
            res.data[2][col] = columns[col].z;
        }
        res.setW(1);
        return res;
    }

    static Matrix viewTransformation(Vector & eye, Vector & look, Vector & up) {

        auto l = (look - eye).normalize();
        auto r = (l * up).normalize();
        auto u = (r * l).normalize();

        // rotation looks like: column([r, u, -l])

        auto rotation = Matrix::rotation(Vector(r.x, u.x, -l.x), Vector(r.y, u.y, -l.y), Vector(r.z, u.z, -l.z));

        auto negatedEye = -eye;
        auto translation = Matrix::translation(negatedEye.x, negatedEye.y, negatedEye.z);

        return (rotation * translation);
    }

    static Matrix projection(double near, double far, double fovY, double aspectRatio) {
        auto res = zero(4, 4);
        auto fovX = fovY * aspectRatio;

        res.data[0][0] = 1 / tan(rad(fovX / 2));
        res.data[1][1] = 1 / tan(rad(fovY / 2));
        res.data[2][2] = -(far + near) / (far - near);
        res.data[2][3] = -(2 * far * near) / (far - near);
        res.data[3][2] = -1;

        return res;
    }

    Matrix operator*(const Matrix &rhs) const {
        int r1 = (int)(*this).data.size();
        int r2 = (int)rhs.data.size();

        int c1 = (int)(*this).data[0].size();
        int c2 = (int)rhs.data[0].size();

        if (c1 != r2) {
            std::cout << "Invalid Matrix Multiplication: " << r1 << "x" << r2 << c1 << "x" << c2 << std::endl;
            return zero(r1, c1);
        }

        auto result = zero(r1, c2);

        for (int i = 0; i < r1; i++) {
            for (int j = 0; j < c2; j++) {
                for (int k = 0; k < c1; k++) {
                    auto d = (*this).data[i][k] * rhs.data[k][j];
                    result.data[i][j] = result.data[i][j] + d;
                }
            }
        }

        return result;
    }

};