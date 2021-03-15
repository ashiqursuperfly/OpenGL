//
// Created by ashiq on 3/14/21.
//
#include "headers/util.h"
#include "headers/rectangle.h"
#include "headers/bubble.h"

#define HEIGHT 600
#define WIDTH 600

Rectangle outerBoundary;
Bubble * bubbles[5];

void initGlobalVariables() {

    outerBoundary = Rectangle(Vector(-WIDTH/5, HEIGHT/5, 0),Vector(WIDTH/5, HEIGHT/5, 0), Vector(-WIDTH/5, -HEIGHT/5, 0),  Vector(WIDTH/5, -HEIGHT/5, 0));

    for (int i = 0; i < 5; i++) {
        Bubble * b = new Bubble(Vector(-WIDTH/5 + 5, -HEIGHT/5 + 5, 0));
        bubbles[i] = b;
    }

}



void makeBubblesVisiblePeriodically(int unused) {

    int i = 0;

    for (i = 0; i < 5; ++i) {
        if (!bubbles[i]->isVisible) {
            bubbles[i]->isVisible = true;
            break;
        }
    }
    if (i < 5) {
        glutTimerFunc(1000, makeBubblesVisiblePeriodically, unused);
    }

}

void drawBubble(int i) {
    glColor3f(1.0, 1.0, 1.0);
    drawCircleXY(bubbles[i]->radius, 50, bubbles[i]->pos);
}

void drawVisibleBubbles() {

    for (int i = 0; i < 5; ++i) {
        if (bubbles[i]->isVisible) {
            drawBubble(i);
        }
    }

}

void display() {

    clearDisplay();

    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    gluLookAt(0, 0, (WIDTH / 4.0f), 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_MODELVIEW);

    drawAxes(WIDTH);

    // TODO: draw objects here
    drawRect(outerBoundary.tl, outerBoundary.tr, outerBoundary.bl, outerBoundary.br);
    drawVisibleBubbles();

    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}

void animate() {

    for (int i = 0; i < 5; ++i) {
        Bubble * b = bubbles[i];

        if (!b->isVisible) break;

        Vector next = b->pos + b->direction;

        if (outerBoundary.contains(next)) {
            b->pos = next;
        }
        else {
            b->direction = -b->direction;
            b->pos = b->pos + b->direction;
        }
    }

    glutPostRedisplay();
}

void init() {

    //clear the screen
    clearDisplay();

    /************************
    / set-up projection here
    ************************/
    //load the PROJECTION matrix
    glMatrixMode(GL_PROJECTION);

    //initialize the matrix
    glLoadIdentity();

    //give PERSPECTIVE parameters
    gluPerspective(80, 1, 1, 1000.0);
    //field of view in the Y (vertically)
    //aspect ratio that determines the field of view in the X direction (horizontally)
    //near distance
    //far distance
}


int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);    //Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    init();
    initGlobalVariables();
    makeBubblesVisiblePeriodically(0);

    glEnable(GL_DEPTH_TEST);    //enable Depth Testing

    glutDisplayFunc(display);
    glutIdleFunc(animate);

    glutMainLoop();        //The main loop of OpenGL

    return 0;
}



