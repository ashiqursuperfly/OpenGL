//
// Created by ashiq on 3/14/21.
//

#include "headers/1605103_opengl_util.h"
#include "headers/1605103_ray_tracing.h"

#define TILE_WIDTH 20

Camera camera;
Scene scene;
RayTracingCapturer rayTracingCapturer(scene);
int numCaptures = 0;

void display() {

    clearDisplay();

    //load the correct matrix -- MODEL-VIEW matrix
    glMatrixMode(GL_MODELVIEW);

    //initialize the matrix
    glLoadIdentity();

    gluLookAt(camera.pos.x, camera.pos.y, camera.pos.z, camera.pos.x + camera.l.x, camera.pos.y + camera.l.y, camera.pos.z + camera.l.z, camera.u.x, camera.u.y, camera.u.z);

    glMatrixMode(GL_MODELVIEW);

    drawAxes(9999);

    scene.draw();

    //ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
    glutSwapBuffers();
}

void animate() {
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
            break;
        case '0':
            rayTracingCapturer.capture("1605103-" + std::to_string(numCaptures++) + ".bmp", 500, 500, scene.pixels, scene.pixels, camera);
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
        Object * obj;
        if (type == "sphere") {
            Sphere s;
            std::cin>>s;
            obj = new Sphere(s.reference_point, s.color, s.radius, s.getAmbient(), s.getDiffuse(), s.getSpecular(), s.getReflection(), s.getShine());
            scene.objects.push_back(obj);
        }

    }

    std::cin>>scene.numLightSources;
    for (int i = 0; i < scene.numLightSources; i++) {
        Light l;
        std::cin>>l;
        scene.lights.push_back(l);
    }
    Object * floor = new Floor(TILE_WIDTH, camera.farPlane);

    floor->setAmbient(0.35);
    floor->setDiffuse(0.25);
    floor->setSpecular(0.15);
    floor->setReflection(0.35);
    floor->setShine(1);

    scene.numObjects += 1;
    scene.objects.push_back(floor);
}

void init() {
    clearDisplay();
    loadData();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(camera.fovy, camera.aspectRatio, camera.nearPlane, camera.farPlane);
}


int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);    //Depth, Double buffer, RGB color

    glutCreateWindow("Ray Tracing");

    init();

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutIdleFunc(animate);

    registerSpecialKeysListener(specialKeyListener);
    registerKeyboardListener(keyboardListener);

    glutMainLoop();

    return 0;
}



