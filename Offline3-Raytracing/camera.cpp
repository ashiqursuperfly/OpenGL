//
// Created by ashiq on 3/14/21.
//

#include "headers/1605103_opengl_util.h"
#include "headers/1605103_camera.h"
#include "headers/1605103_objects.h"

#define FOVY 80
#define ASPECT_RATIO 1
#define NEAR_PLANE 1
#define FAR_PLANE 1000
#define TILE_WIDTH 20

Camera camera;
Floor floorB(TILE_WIDTH, FAR_PLANE);
Scene scene;


void display() {

    clearDisplay();

    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    gluLookAt(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.x + camera.l.x, camera.pos.y + camera.l.y, camera.pos.z + camera.l.z, camera.u.x, camera.u.y, camera.u.z);

    glMatrixMode(GL_MODELVIEW);

    drawAxes(9999);

    floorB.draw();
    scene.draw();

    glColor3f(1.0, 1.0, 1.0);

    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}

void animate() {
    glutPostRedisplay();
}

void keyboardListener(unsigned char key, int x, int y) {

    switch (key) {

        case '1':
            camera.l = camera.l.rotate(camera.u, 3.0);
            camera.r = camera.l * camera.u;
            camera.print();
            break;
        case '2':
            camera.l = camera.l.rotate(camera.u, -3.0);
            camera.r = camera.l * camera.u;
            camera.print();
            break;
        case '3':
            camera.l = camera.l.rotate(camera.r, 3.0);
            camera.u = camera.r * camera.l;
            camera.print();
            break;
        case '4':
            camera.l = camera.l.rotate(camera.r, -3.0);
            camera.u = camera.r * camera.l;
            camera.print();
            break;
        case '5':
            camera.r = camera.r.rotate(camera.l, -3.0);
            camera.u = camera.r * camera.l;
            camera.print();
            break;
        case '6':
            camera.r = camera.r.rotate(camera.l, 3.0);
            camera.u = camera.r * camera.l;
            camera.print();
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

void loadData() {

    FILE *fp = freopen("scene.txt", "r", stdin);

    if (fp == nullptr) {
        std::cout << "Error: Input File Not Found" << std::endl;
        return;
    }

    std::cin>>scene.recursionLevels;
    std::cin>>scene.pixels;
    std::cin>>scene.numObjects;

    for (int i = 0; i < scene.numObjects; ++i) {
        std::string type;
        std::cin>>type;
        if (type == "sphere") {
            Sphere s;
            std::cin>>s;
            scene.spheres.push_back(s);
        }
    }

    std::cin>>scene.numLightSources;
    for (int i = 0; i < scene.numLightSources; i++) {
        Light l;
        std::cin>>l;
        scene.lights.push_back(l);
    }



}

void init() {
    clearDisplay();
    loadData();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE);
}


int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);    //Depth, Double buffer, RGB color

    glutCreateWindow("Ray Tracing Demo");

    init();

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutIdleFunc(animate);

    registerSpecialKeysListener(specialKeyListener);
    registerKeyboardListener(keyboardListener);

    glutMainLoop();

    return 0;
}



