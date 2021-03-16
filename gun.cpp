//
// Created by ashiq on 3/14/21.
//

#include "headers/util.h"

/**
 * Marks:
 * draw sphere: 4
 * drawing cylinder with its parts 10
 * handling rotations 12
 * drawing bullets on plane
 */

Rotation er = Rotation(Vector(0, 1, 0), 0);
Rotation qw = Rotation(Vector(1, 0, 0), 0);
Rotation df = Rotation(Vector(0, 0, 1), 0);
Camera camera;

void display() {

    clearDisplay();

    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    gluLookAt(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.x + camera.l.x, camera.pos.y + camera.l.y, camera.pos.z + camera.l.z, camera.u.x, camera.u.y, camera.u.z);

    glMatrixMode(GL_MODELVIEW);


    drawAxes(9999);
    // glColor3f(1.0, 1.0, 1.0);
    //drawGrid(6, 80, 10);

    glColor3f(1.0, 1.0, 1.0);


    drawGunBarrel(5, 30, 50, 200, Vector(0, 0, 0), qw, er);
    drawGunTip(4.5,5.2, 33, 50, 200, Vector(0, 0, 0), qw, er, df);



    // TODO: draw objects here

    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}

void animate() {
    // TODO: what you want to do in the idle time (when no drawing is occuring)
    glutPostRedisplay();
}

void keyboardListener(unsigned char key, int x, int y) {

    switch (key) {

        case '1':
            camera.l = camera.l.rotate(camera.u, 1.5);
            camera.r = camera.l * camera.u;
            camera.print();
            break;
        case '2':
            camera.l = camera.l.rotate(camera.u, -1.5);
            camera.r = camera.l * camera.u;
            camera.print();
            break;
        case '3':
            camera.l = camera.l.rotate(camera.r, 1.5);
            camera.u = camera.r * camera.l;
            camera.print();
            break;
        case '4':
            camera.l = camera.l.rotate(camera.r, -1.5);
            camera.u = camera.r * camera.l;
            camera.print();
            break;
        case '5':
            camera.r = camera.r.rotate(camera.l, -1.5);
            camera.u = camera.r * camera.l;
            camera.print();
            break;
        case '6':
            camera.r = camera.r.rotate(camera.l, 1.5);
            camera.u = camera.r * camera.l;
            camera.print();

        case 'q':
            qw.updateAngle(3.0);
            break;
        case 'w':
            qw.updateAngle(-3.0);
            break;
        case 'e':
            er.updateAngle(3.0);
            break;
        case 'r':
            er.updateAngle(-3.0);
            break;
        case 'd':
            df.updateAngle(3.0);
            break;
        case 'f':
            df.updateAngle(-3.0);
            break;
        default:
            break;
    }
}

void specialKeyListener(int key, int x, int y) {

    switch (key) {

        case GLUT_KEY_UP:
            camera.pos = camera.pos + camera.l;
            camera.print();
            break;

        case GLUT_KEY_DOWN:
            camera.pos = camera.pos - camera.l;
            camera.print();
            break;

        case GLUT_KEY_RIGHT:
            camera.pos = camera.pos + camera.r;
            camera.print();
            break;

        case GLUT_KEY_LEFT:
            camera.pos = camera.pos - camera.r;
            camera.print();
            break;

        case GLUT_KEY_PAGE_UP:
            camera.pos = camera.pos + camera.u;
            camera.print();
            break;

        case GLUT_KEY_PAGE_DOWN:
            camera.pos = camera.pos - camera.u;
            camera.print();
            break;

        default:
            break;

    }

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
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);    //Depth, Double buffer, RGB color

    glutCreateWindow("My OpenGL Program");

    init();

    glEnable(GL_DEPTH_TEST);    //enable Depth Testing

    glutDisplayFunc(display);
    glutIdleFunc(animate);

    // TODO: register listeners here
    registerSpecialKeysListener(specialKeyListener);
    registerKeyboardListener(keyboardListener);

    glutMainLoop();        //The main loop of OpenGL

    return 0;
}



