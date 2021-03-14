//
// Created by ashiq on 3/14/21.
//
#include "util.h"

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

            /* case GLUT_KEY_PAGE_UP:
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
            */
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

void animate() {
    // TODO:
    //what you want to do in the idle time (when no drawing is occuring)
    glutPostRedisplay();
}

void display() {

    clearDisplay();

    /********************
    / set-up camera here
    ********************/
    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    //now give three info
    //1. where is the camera (viewer)?
    //2. where is the camera looking?
    //3. Which direction is the camera's UP direction?

    //gluLookAt(100,100,100,	0,0,0,	0,0,1);
    //gluLookAt(200*cos(cameraAngle), 200*sin(cameraAngle), cameraHeight,		0,0,0,		0,0,1);
    gluLookAt(0, 0, 200, 0, 0, 0, 0, 1, 0);


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);

    drawAxes();
    drawGrid();

    // TODO: draw objects here

    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
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

    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);
    glutMouseFunc(mouseListener);

    glutMainLoop();        //The main loop of OpenGL

    return 0;
}

