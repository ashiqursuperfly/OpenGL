//
// Created by ashiq on 3/14/21.
//

#include "headers/util.h"
#include "headers/rectangle.h"
#include "headers/bubble.h"
#include "headers/circle.h"

#define HEIGHT 600
#define WIDTH 600
#define BUBBLE_COUNT 5

bool PAUSE = false;

Circle innerBoundary;
Rectangle outerBoundary;
Bubble * bubbles[BUBBLE_COUNT];

void initGlobalVariables() {

    innerBoundary = Circle(Vector(0, 0, 0), 50);
    outerBoundary = Rectangle(Vector(-WIDTH/7.0, HEIGHT/7.0, 0),Vector(WIDTH/7.0, HEIGHT/7.0, 0), Vector(-WIDTH/7.0, -HEIGHT/7.0, 0),  Vector(WIDTH/7.0, -HEIGHT/7.0, 0));

    for (int i = 0; i < BUBBLE_COUNT; i++) {
        Bubble * b = new Bubble();
        b->pos = Vector(-WIDTH/7.0 + b->radius, -HEIGHT/7.0 + b->radius, 0);
        bubbles[i] = b;
        b->print();
    }
}

void specialKeyListener(int key, int x, int y) {

    switch (key) {

        case GLUT_KEY_UP:
            Bubble::updateSpeed(0.01);
            break;

        case GLUT_KEY_DOWN:
            Bubble::updateSpeed(-0.01);
            break;

        case GLUT_KEY_F1:
            PAUSE = 1 - PAUSE;
            break;

        default:
            break;

    }

}

void makeBubblesVisiblePeriodically(int unused) {

    int i = 0;

    for (i = 0; i < BUBBLE_COUNT; ++i) {
        if (!bubbles[i]->isVisible) {
            bubbles[i]->isVisible = true;
            break;
        }
    }
    if (i < BUBBLE_COUNT) {
        glutTimerFunc(5000, makeBubblesVisiblePeriodically, unused);
    }

}

void drawBubble(int i) {
    glColor3f(1.0, 1.0, 1.0);
    drawCircleXY(bubbles[i]->radius, 50, bubbles[i]->pos);
}

void drawVisibleBubbles() {

    for (int i = 0; i < BUBBLE_COUNT; ++i) {
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

    // drawAxes(WIDTH);

    // TODO: draw objects here
    glColor3f(0, 1.0, 0);
    drawRectXY(outerBoundary.tl, outerBoundary.tr, outerBoundary.bl, outerBoundary.br);
    glColor3f(1.0, 0, 0);
    drawCircleXY(innerBoundary.radius, 50, innerBoundary.center);
    drawVisibleBubbles();

    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}

void outerBoundaryLogic() {
    for (int i = 0; i < BUBBLE_COUNT && !PAUSE ; ++i) {

        Bubble * b = bubbles[i];

        if (!b->isVisible || b->state == INNER) continue;

        Vector next = b->pos + (b->direction * Bubble::speed);

        switch (outerBoundary.contains(next)) {
            case NO_COLLISION:
                b->pos = next;
                if (innerBoundary.contains(b->pos, b->radius)) {
                    b->state = INNER;
                }
                break;
            case L_R_WALL:
                b->direction = Vector(-b->direction.x, b->direction.y, b->direction.z);
                break;
            case T_B_WALL:
                b->direction = Vector(b->direction.x, -b->direction.y, b->direction.z);
                break;
        }

    }
}

void bubbleBubbleCollisionLogic() {

    for (int i = 0; i < BUBBLE_COUNT && !PAUSE ; ++i) {

        Bubble * b1 = bubbles[i];

        if (!b1->isVisible || b1->state == OUTER) continue;

        for (int j = 0; j < BUBBLE_COUNT && !PAUSE; ++j) {
            if (i == j) continue;

            Bubble * b2 = bubbles[j];

            if (b2->state == OUTER) continue;

            if (b1->checkCollision(*b2)) {
                //TODO: do actual reflection
                Vector n = (b1->pos - b2->pos).normalize();
                Vector r1 = b1->direction - n * (2 * (n.dot(b1->direction)));
                Vector r2 = b2->direction - n * (2 * (n.dot(b2->direction)));
                b1->direction = r1.normalize();
                b2->direction = r2.normalize();
                b1->pos = b1->pos + (b1->direction * Bubble::speed);
                b2->pos = b2->pos + (b2->direction * Bubble::speed);
            }


        }

    }

}

void innerBoundaryLogic() {
    for (int i = 0; i < BUBBLE_COUNT && !PAUSE ; ++i) {

        Bubble * b = bubbles[i];

        if (!b->isVisible || b->state == OUTER) continue;

        Vector next = b->pos + (b->direction * Bubble::speed);

        if (!innerBoundary.contains(next, b->radius)) {
            Vector n = innerBoundary.center - next;
            n = n.normalize();
            Vector r = b->direction - n * (2 * (n.dot(b->direction)));
            b->direction = r.normalize();
        }
        else {
            b->pos = next;
        }

    }
}


void animate() {
    outerBoundaryLogic();
    innerBoundaryLogic();
    bubbleBubbleCollisionLogic();
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

    registerSpecialKeysListener(specialKeyListener);

    glutMainLoop();        //The main loop of OpenGL

    return 0;
}



