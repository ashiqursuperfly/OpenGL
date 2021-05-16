//
// Created by ashiq on 5/15/21.
//

#ifndef OFFLINE2_1605103_MATRIX_H
#define OFFLINE2_1605103_MATRIX_H

#endif //OFFLINE2_1605103_MATRIX_H


// TODO: REFACTOR THIS CLASS

class Matrix {

public:
    std::vector<std::vector<double>> data;

    Matrix() = default;

    Matrix(int r, int c) {
        std::vector<double> row(c, 0);
        for (int i = 0; i < r; i++) {
            data.push_back(row);
        }
    }

    Matrix(const Matrix &m) {
        this->data = m.data;
    }

    double getW() {
        return data[data.size() - 1][data[0].size() - 1];
    }

    void setW(double val) {
        data[data.size() - 1][data[0].size() - 1] = val;
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &m) {
        for (const auto &row : m.data) {
            for (auto cell : row) {
                os << cell << ' ';
            }
            os << std::endl;
        }
        return os;
    }

    Matrix operator*(const Matrix &rhs) const {
        int r1 = (int)(*this).data.size(), c1 = (int)(*this).data[0].size();
        int r2 = (int)rhs.data.size(), c2 = (int)rhs.data[0].size();

        if (c1 != r2) {
            std::cout << "Invalid Matrix Multiplication: " << r1 << "x" << r2 << c1 << "x" << c2 << endl;
            return ZeroMatrix(r1, c2);
        }

        auto result = ZeroMatrix(r1, c2);

        for (auto i = 0; i < r1; i++) {
            for (auto j = 0; j < c2; j++) {
                for (auto k = 0; k < c1; k++) {
                    result.data[i][j] += (*this).data[i][k] * rhs.data[k][j];
                }
            }
        }

        return result;
    }

    static Matrix IdentityMatrix(int r = 4, int c = 4) {
        auto res = ZeroMatrix(r, c);
        for (int i = 0; i < res.data.size(); i++) {
            res.data[i][i] = 1;
        }
        return res;
    }

    static Matrix ZeroMatrix(int r, int c) {
        return Matrix(r, c);
    }

    static Matrix ColumnMatrix(const Vector &Vector) {
        auto res = ZeroMatrix(4, 1);

        res.data[0][0] = Vector.x;
        res.data[1][0] = Vector.y;
        res.data[2][0] = Vector.z;
        res.data[3][0] = 1;
        return res;
    }

    static Matrix TranslationMatrix(double dx, double dy, double dz) {
        auto res = IdentityMatrix(4, 4);

        res.data[0][3] = dx;
        res.data[1][3] = dy;
        res.data[2][3] = dz;
        return res;
    }

    static Matrix ScalingMatrix(double sx, double sy, double sz) {
        auto res = ZeroMatrix(4, 4);

        res.data[0][0] = sx;
        res.data[1][1] = sy;
        res.data[2][2] = sz;
        res.setW(1);

        return res;
    }

    static Matrix RotationMatrix(Vector col0, Vector col1, Vector col2) {

        auto res = ZeroMatrix(4, 4);

        std::vector<Vector> col = {col0, col1, col2};

        for (int c = 0; c < 3; ++c) {
            res.data[0][c] = col[c].x;
            res.data[1][c] = col[c].y;
            res.data[2][c] = col[c].z;
        }

        res.setW(1);
        return res;
    }

    static Matrix ProjectionMatrix(double near, double far, double fovY, double aspectRatio) {
        auto res = ZeroMatrix(4, 4);
        auto fovX = fovY * aspectRatio;

        res.data[0][0] = 1 / tan(rad(fovX / 2));
        res.data[1][1] = 1 / tan(rad(fovY / 2));
        res.data[2][2] = -(far + near) / (far - near);
        res.data[2][3] = -(2 * far * near) / (far - near);
        res.data[3][2] = -1;

        return res;
    }

    static Matrix ViewTransformationMatrix(Vector & eye, Vector & look, Vector & up) {

        auto l = (look - eye).normalize();
        auto r = (l * up).normalize();
        auto u = (r * l).normalize();

        // rotation looks like: column([r, u, -l])

        auto rotation = Matrix::RotationMatrix(Vector(r.x, u.x, -l.x), Vector(r.y, u.y, -l.y), Vector(r.z, u.z, -l.z));

        auto negatedEye = -eye;
        auto translation = Matrix::TranslationMatrix(negatedEye.x, negatedEye.y, negatedEye.z);

        return (rotation * translation);
    }

};