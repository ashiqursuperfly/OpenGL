//
// Created by ashiq on 5/15/21.
//

#ifndef OFFLINE2_1605103_MATRIX_H
#define OFFLINE2_1605103_MATRIX_H

#endif //OFFLINE2_1605103_MATRIX_H


// TODO: REFACTOR THIS CLASS

class Matrix {

public:
    std::vector<std::vector<double>> matrix;

    Matrix() = default;

    Matrix(int r, int c) {
        std::vector<double> row(c, 0);
        for (int i = 0; i < r; i++) {
            matrix.push_back(row);
        }
    }

    Matrix(const Matrix &m) {
        this->matrix = m.matrix;
    }

    double &W() {
        return matrix[matrix.size() - 1][matrix[0].size() - 1];
    }

    friend std::ostream &operator<<(std::ostream &os, const Matrix &m) {
        for (const auto &row : m.matrix) {
            for (auto cell : row) {
                os << cell << ' ';
            }
            os << std::endl;
        }
        return os;
    }

    Matrix operator*(const Matrix &B) const {
        const auto &A = *this;
        auto rA = A.matrix.size(), cA = A.matrix[0].size();
        auto rB = B.matrix.size(), cB = B.matrix[0].size();

        if (cA != rB) {
            std::cout << "Multiplication Dimension error!\n";
            return ZeroMatrix(rA, cB);
        }

        auto C = ZeroMatrix(rA, cB);

        for (auto i = 0; i < rA; i++) {
            for (auto j = 0; j < cB; j++) {
                for (auto k = 0; k < cA; k++) {
                    C.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
                }
            }
        }

        return C;
    }

    static Matrix ZeroMatrix(int r, int c) {
        return Matrix(r, c);
    }

    static Matrix ColumnMatrix(const Vector &Vector) {
        auto a = ZeroMatrix(4, 1);

        a.matrix[0][0] = Vector.x;
        a.matrix[1][0] = Vector.y;
        a.matrix[2][0] = Vector.z;
        a.matrix[3][0] = 1;
        return a;
    }

    static Matrix IdentityMatrix(int r = 4, int c = 4) {
        auto a = ZeroMatrix(r, c);
        for (int i = 0; i < a.matrix.size(); i++) {
            a.matrix[i][i] = 1;
        }
        return a;
    }

    static Matrix TranslationMatrix(double dx, double dy, double dz) {
        auto a = IdentityMatrix(4, 4);

        a.matrix[0][3] = dx;
        a.matrix[1][3] = dy;
        a.matrix[2][3] = dz;
        return a;
    }

    static Matrix TranslationMatrix(Vector d) {
        auto a = IdentityMatrix(4, 4);

        a.matrix[0][3] = d.x;
        a.matrix[1][3] = d.y;
        a.matrix[2][3] = d.z;
        return a;
    }

    static Matrix ScalingMatrix(double sx, double sy, double sz) {
        auto a = ZeroMatrix(4, 4);

        a.matrix[0][0] = sx;
        a.matrix[1][1] = sy;
        a.matrix[2][2] = sz;
        a.W() = 1;

        return a;
    }

    static Matrix ScalingMatrix(Vector s) {
        auto a = ZeroMatrix(4, 4);

        a.matrix[0][0] = s.x;
        a.matrix[1][1] = s.y;
        a.matrix[2][2] = s.z;
        a.W() = 1;

        return a;
    }

    static Matrix RotationMatrix(Vector col0, Vector col1, Vector col2) {

        auto a = ZeroMatrix(4, 4);

        std::vector<Vector> col = {col0, col1, col2};

        for (int c = 0; c < 3; ++c) {
            a.matrix[0][c] = col[c].x;
            a.matrix[1][c] = col[c].y;
            a.matrix[2][c] = col[c].z;
        }

        a.W() = 1;
        return a;
    }

    static Matrix ProjectionMatrix(double near, double far, double fovY, double aspectRatio) {
        auto a = ZeroMatrix(4, 4);

        auto fovX = fovY * aspectRatio;
        auto t = near * tan(rad(fovY / 2));
        auto r = near * tan(rad(fovX / 2));

        a.matrix[0][0] = near / r;
        a.matrix[1][1] = near / t;

        a.matrix[2][2] = -(far + near) / (far - near);
        a.matrix[2][3] = -(2 * far * near) / (far - near);

        a.matrix[3][2] = -1;

        return a;
    }

    static Matrix ViewTransformationMatrix(Vector & eye, Vector & look, Vector & up) {

        auto l = (look - eye).normalize();
        auto r = (l * up).normalize();
        auto u = (r * l).normalize();

        auto col1 = Vector(r.x, u.x, -l.x);
        auto col2 = Vector(r.y, u.y, -l.y);
        auto col3 = Vector(r.z, u.z, -l.z);

        return (Matrix::RotationMatrix(col1, col2, col3) * Matrix::TranslationMatrix(-eye));
    }

};