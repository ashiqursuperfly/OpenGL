//
// Created by ashiq on 3/14/21.
//

#ifndef OFFLINE1_UTIL_H
#define OFFLINE1_UTIL_H

#endif //OFFLINE1_UTIL_H

#include<cmath>
#include <GL/glut.h>
#include <iostream>

#define pi (2*acos(0.0))

class Vector {
public:
    double x, y, z;

    Vector operator+ (Vector const &rhs) const {

        Vector res;

        res.x = x + rhs.x;
        res.y = y + rhs.y;
        res.z = z + rhs.z;

        return res;
    }

    Vector operator- (Vector const &rhs) const {

        Vector res;

        res.x = x - rhs.x;
        res.y = y - rhs.y;
        res.z = z - rhs.z;

        return res;
    }

    Vector operator- () const {

        Vector res;

        res.x = -x;
        res.y = -y;
        res.z = -z;

        return res;
    }

    Vector operator* (Vector const & rhs) const {

        Vector res;

        res.x = y * rhs.z - z * rhs.y;
        res.y = z * rhs.x - x * rhs.z;
        res.z = x * rhs.y - y * rhs.x;

        return res;

    }

    Vector operator* (double scalar) const {

        Vector a;

        if (scalar != 0){
            a.x = x * scalar;
            a.y = y * scalar;
            a.z = z * scalar;
        }

        return a;
    }


    Vector rotate(Vector const & axis, double angleDegrees)
    {
        //rotate this vector with respect to an axis
        Vector crossProduct = axis * (*this);

        // r1 = lxCost , lyCost
        // r2 = rxSint , rySint
        // res = (lxCost + rxSint) , (lyCost + rySint)

        Vector r1 = (*this) * cos(angleDegrees * pi / 180);
        Vector r2 = crossProduct * sin(angleDegrees * pi / 180.0);

        return r1 + r2;
    }

    void print() const {
        std::cout<<"( "<<x<<","<<y<<","<<z<<" )"<<std::endl;
    }
};



void drawAxes(int len) {


    glBegin(GL_LINES);

    {
        // x-axis
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(len, 0, 0);
        glVertex3f(-len, 0, 0);

        // y-axis
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0, -len, 0);
        glVertex3f(0, len, 0);

        // z-axis
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0, 0, len);
        glVertex3f(0, 0, -len);
    }

    glEnd();


}


void drawGrid(int lines, int len, int spacing) {

    int i;

    glBegin(GL_LINES);

    {
        for (i = -lines; i <= lines; i++) {

            if (i == 0)
                continue;    //SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i * spacing, -len, 0);
            glVertex3f(i * spacing, len, 0);

            //lines parallel to X-axis
            glVertex3f(-len, i * spacing, 0);
            glVertex3f(len, i * spacing, 0);
        }
    }

    glEnd();


}


void drawSquare(double a) {

    //glColor3f(1.0,0.0,0.0);
    glBegin(GL_QUADS);

    {
        glVertex3f(a, a, 2);
        glVertex3f(a, -a, 2);
        glVertex3f(-a, -a, 2);
        glVertex3f(-a, a, 2);
    }

    glEnd();
}


void drawCircle(double radius, int segments) {

    int i;
    Vector points[100];

    //generate points
    for (i = 0; i <= segments; i++) {
        points[i].x = radius * cos(((double) i / (double) segments) * 2 * pi);
        points[i].y = radius * sin(((double) i / (double) segments) * 2 * pi);
    }

    //draw segments using generated points
    for (i = 0; i < segments; i++) {
        glBegin(GL_LINES);
        {
            glVertex3f(points[i].x, points[i].y, 0);
            glVertex3f(points[i + 1].x, points[i + 1].y, 0);
        }
        glEnd();
    }
}


void drawCone(double radius, double height, int segments) {

    int i;
    double shade;
    Vector points[100];

    //generate points
    for (i = 0; i <= segments; i++) {
        points[i].x = radius * cos(((double) i / (double) segments) * 2 * pi);
        points[i].y = radius * sin(((double) i / (double) segments) * 2 * pi);
    }

    //draw triangles using generated points
    for (i = 0; i < segments; i++) {
        //create shading effect
        if (i < segments / 2)shade = 2 * (double) i / (double) segments;
        else shade = 2 * (1.0 - (double) i / (double) segments);

        glBegin(GL_TRIANGLES);

        {
            glVertex3f(0, 0, height);
            glVertex3f(points[i].x, points[i].y, 0);
            glVertex3f(points[i + 1].x, points[i + 1].y, 0);
        }

        glEnd();
    }
}


void drawSphere(double radius, int slices, int stacks) {

    Vector points[100][100];
    int i, j;
    double h, r;

    //generate points
    for (i = 0; i <= stacks; i++) {
        h = radius * sin(((double) i / (double) stacks) * (pi / 2));
        r = radius * cos(((double) i / (double) stacks) * (pi / 2));
        for (j = 0; j <= slices; j++) {
            points[i][j].x = r * cos(((double) j / (double) slices) * 2 * pi);
            points[i][j].y = r * sin(((double) j / (double) slices) * 2 * pi);
            points[i][j].z = h;
        }
    }

    //draw quads using generated points
    for (i = 0; i < stacks; i++) {
        // glColor3f((double) i / (double) stacks, (double) i / (double) stacks, (double) i / (double) stacks);
        for (j = 0; j < slices; j++) {
            glBegin(GL_QUADS);

            {
                //upper hemisphere
                glVertex3f(points[i][j].x, points[i][j].y, points[i][j].z);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, points[i][j + 1].z);
                glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, points[i + 1][j + 1].z);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, points[i + 1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x, points[i][j].y, -points[i][j].z);
                glVertex3f(points[i][j + 1].x, points[i][j + 1].y, -points[i][j + 1].z);
                glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, -points[i + 1][j + 1].z);
                glVertex3f(points[i + 1][j].x, points[i + 1][j].y, -points[i + 1][j].z);
            }

            glEnd();
        }
    }
}

void clearDisplay() {
    //clear the display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);    //color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void registerKeyboardListener(void (*listener)(unsigned char, int, int)) {
    glutKeyboardFunc(listener);
}

void registerMouseListener(void (*listener)(int, int, int, int)) {
    glutMouseFunc(listener);
}

void registerSpecialKeysListener(void (*listener)(int, int, int)) {
    glutSpecialFunc(listener);
}


/*
void keyboardListener(unsigned char key, int x, int y) {

    switch (key) {
        case '1':
            break;

        default:
            break;
    }

}


void specialKeyListener(int key, int x, int y) {

    switch (key) {

        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_UP:
            break;

        case GLUT_KEY_RIGHT:
            break;
        case GLUT_KEY_LEFT:
            break;


        case GLUT_KEY_PAGE_UP:
            break;
        case GLUT_KEY_PAGE_DOWN:
            break;

        case GLUT_KEY_INSERT:
            break;

        case GLUT_KEY_HOME:
            break;
        case GLUT_KEY_END:
            break;

        default:
            break;


    }

}


void mouseListener(int button, int state, int x, int y) {    //x, y is the x-y of the screen (2D)

    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {        // 2 times?? in ONE click? -- solution is checking DOWN or UP
            }
            break;

        case GLUT_RIGHT_BUTTON:
            //........
            break;

        case GLUT_MIDDLE_BUTTON:
            //........
            break;

        default:
            break;
    }
}

*/









