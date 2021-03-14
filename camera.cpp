//
// Created by ashiq on 3/14/21.
//
#include "util.h"

class Camera {
public:

    Vector pos;
    Vector u, r, l;

    Camera() {

        pos = Vector();
        pos.x = 0;
        pos.y = 0;
        pos.z = 0;

        u.x = 0;
        u.y = 0;
        u.z = 1;

        r.x = -1 / sqrt(2.0);
        r.y = 1 / sqrt(2.0);
        r.z = 0;

        l = u.cross(r);

        print();
    }

    void print() const {
        std::cout<<"Pos:";
        pos.print();
        std::cout<<"l:";
        l.print();
        std::cout<<"r:";
        r.print();
        std::cout<<"u:";
        u.print();
    }
};

Camera camera;

void specialKeyListener(int key, int x, int y) {

    switch (key) {

        case GLUT_KEY_DOWN:
            camera.pos = camera.pos.sum(camera.l.negate());
            break;

        case GLUT_KEY_UP:
            camera.pos = camera.pos.sum(camera.l);
            break;

        case GLUT_KEY_RIGHT:
            camera.pos = camera.pos.sum(camera.r);
            break;

        case GLUT_KEY_LEFT:
            camera.pos = camera.pos.sum(camera.r.negate());
            break;

        case GLUT_KEY_PAGE_UP:
            camera.pos = camera.pos.sum(camera.u);
            break;

        case GLUT_KEY_PAGE_DOWN:
            camera.pos = camera.pos.sum(camera.u.negate());
            break;

        /*
            case GLUT_KEY_INSERT:
                break;

            case GLUT_KEY_HOME:
                break;
            case GLUT_KEY_END:
                break;
        */

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
    // TODO: what you want to do in the idle time (when no drawing is occuring)
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
    gluLookAt(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.x + camera.l.x, camera.pos.y + camera.l.y, camera.pos.z + camera.l.z, camera.u.x, camera.u.y, camera.u.z);


    //again select MODEL-VIEW
    glMatrixMode(GL_MODELVIEW);

    glColor3f(0.0, 1.0, 0.0);
    drawAxes();
    glColor3f(1.0, 1.0, 1.0);
    drawGrid();
    glColor3f(1.0, 0.0, 0.0);
    drawSphere(50, 30, 50);

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

    // TODO: register listeners here
    registerSpecialKeysListener(specialKeyListener);

    glutMainLoop();        //The main loop of OpenGL

    return 0;
}



