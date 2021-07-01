//
// Created by ashiq on 6/24/21.
//

#ifndef OFFLINE3_1605103_OBJECTS_H
#define OFFLINE3_1605103_OBJECTS_H

#endif //OFFLINE3_1605103_OBJECTS_H

#include <vector>
#include "1605103_color.h"

class Floor {
public:
    int tileWidth;
    int width;

    Floor(int tw, int w) {
        tileWidth = tw;
        width = w;
    }

    void draw() const {
        glPushMatrix();
        double color = 0;
        int leftLim = -5 * width;
        int rightLimit = 5 * width;
        for (int i = leftLim; i < rightLimit; i += tileWidth) {
            for (int j = leftLim; j < rightLimit; j += tileWidth) {
                color = 1 - color;
                glColor3f(color, color, color);

                glBegin(GL_QUADS);
                {
                    glVertex2f(i, j);

                    glVertex2f(i + tileWidth, j);

                    glVertex2f(i + tileWidth, j + tileWidth);

                    glVertex2f(i, j + tileWidth);

                }
                glEnd();
            }
            color = 1 - color;
        }
        glPopMatrix();
    }


};

class Object {
    std::vector<double> coEfficients;
    int shine;
public:
    Vector reference_point;
    Color color;

    Object() {
        reference_point = {0, 0, 0};
        shine = 0;
        coEfficients.push_back(0);
        coEfficients.push_back(0);
        coEfficients.push_back(0);
        coEfficients.push_back(0);
    }

    double getAmbient() {
        return coEfficients[0];
    }

    void setAmbient(double val) {
        coEfficients[0] = val;
    }

    double getDiffuse() {
        return coEfficients[1];
    }

    void setDiffuse(double val) {
        coEfficients[1] = val;
    }

    double getSpecular() {
        return coEfficients[2];
    }

    void setSpecular(double val) {
        coEfficients[2] = val;
    }

    double getReflection() {
        return coEfficients[3];
    }

    void setReflection(double val) {
        coEfficients[3] = val;
    }

    int getShine() {
        return shine;
    }

    void setShine(int shine) {
        this->shine = shine;
    }

    virtual void draw() const{}

};

class Sphere : Object {
public:
    double radius;

    Sphere() {
        radius = 0;
    }

    Sphere(Vector center, double radius, double ambient, double diffuse, double specular, double reflection,int shine) {
        reference_point = center;
        this->radius = radius;

        setAmbient(ambient);
        setDiffuse(diffuse);
        setSpecular(specular);
        setReflection(reflection);
        setShine(shine);
    }

    void draw() const override {
        glPushMatrix();
        glTranslatef(reference_point.x, reference_point.y, reference_point.z);
        glColor3f(color.r, color.g, color.b);

        struct Vector points[100][100];
        int i, j;
        double h, r;
        int slices = 80, stacks = 80;
        for (i = 0; i <= stacks; i++) {
            h = radius * sin(((double) i / (double) stacks) * (pi / 2));
            r = radius * cos(((double) i / (double) stacks) * (pi / 2));
            for (j = 0; j <= slices; j++) {
                points[i][j].x = r * cos(((double) j / (double) slices) * 2 * pi);
                points[i][j].y = r * sin(((double) j / (double) slices) * 2 * pi);
                points[i][j].z = h;
            }
        }

        for (i = 0; i < stacks; i++) {
            for (j = 0; j < slices; j++) {
                glBegin(GL_QUADS);
                {
                    glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);
                    glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);
                    glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, points[i + 1][j + 1].z);
                    glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);

                    glVertex3f(points[i][j].x, points[i][j].y, -points[i][j].z);
                    glVertex3f(points[i][j + 1].x, points[i][j + 1].y, -points[i][j + 1].z);
                    glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, -points[i + 1][j + 1].z);
                    glVertex3f(points[i + 1][j].x, points[i + 1][j].y, -points[i + 1][j].z);
                }
                glEnd();
            }
        }
        glPopMatrix();
    }
    friend std::istream &operator>>(std::istream &is, Sphere &v) {
        is >> v.reference_point;
        is >> v.radius;
        is >> v.color;

        double c1, c2, c3, c4;
        int c5;

        is >> c1;
        v.setAmbient(c1);

        is >> c2;
        v.setDiffuse(c2);

        is >> c3;
        v.setSpecular(c3);

        is >> c4;
        v.setReflection(c4);

        is >> c5;
        v.setShine(c5);

        return is;
    }

};

class Light {
public:
    Vector position;
    Color color;

    friend std::ostream &operator<<(std::ostream &os, const Light &v) {
        os <<"Light P:"<<v.position;
        os <<" Light C:"<<v.color<<std::endl;
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Light &v) {
        is >> v.position;
        is >> v.color;
        return is;
    }
    void draw() const{
        glColor3f(color.r, color.g, color.b);
        glPushMatrix();
        {
            glTranslatef(position.x, position.y, position.z);
            glutSolidSphere(0.5, 7, 7);
        }
        glPopMatrix();
    }

};

class Scene {
public:
    int numObjects;
    int numLightSources;
    int recursionLevels;
    int pixels;

    std::vector<Sphere> spheres;
    std::vector<Light> lights;

    void draw() const {
        for (const auto & sphere : spheres) {
            sphere.draw();
        }
        for (const Light & light : lights) {
            light.draw();
        }
    }
};