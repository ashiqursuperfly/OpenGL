//
// Created by ashiq on 3/17/21.
//

#ifndef OFFLINE1_GUN_H
#define OFFLINE1_GUN_H

#endif //OFFLINE1_GUN_H

class Gun {
private:
    int stacks = 200;
    int slices = 50;
    float barrelRadius = 5.0;
    float barrelLength = 50.0;
    float tipInnerRadius = barrelRadius * 0.6f;
    float tipOutRadius = barrelRadius * 1.1f;
    float tipLength = barrelLength + 3;
    Vector center = Vector(0, 0, 0);


public:
    Rotation er = Rotation(Vector(0, 1, 0), 0);
    Rotation qw = Rotation(Vector(1, 0, 0), 0);
    Rotation df = Rotation(Vector(0, 0, 0), 0);

    void drawTip() {
        Vector points[stacks + 1][slices + 1];
        int i, j;
        double h, r;

        // generate points
        for (i = 0; i <= stacks; i++) {
            h = tipLength * sin(((double) i / (double) stacks) * (pi / 2));
            r = tipOutRadius - tipOutRadius * cos(((double) i / (double) stacks) * (pi / 2)) + tipInnerRadius;

            for (j = 0; j <= slices; j++) {
                double angle = ((double) j / (double) slices) * 2 * pi;
                angle += df.angleDegrees;
                points[i][j].x = r * cos(angle) + center.x;
                points[i][j].y = r * sin(angle) + center.y;
                points[i][j].z = h;
                points[i][j] = points[i][j].rotate(qw.axis, qw.angleDegrees);
                points[i][j] = points[i][j].rotate(er.axis, er.angleDegrees);
            }
        }

        int color = 0;
        //draw quads using generated points
        for (i = 0; i < stacks; i++) {
            // glColor3f((double) i / (double) stacks, (double) i / (double) stacks, (double) i / (double) stacks);
            for (j = 0; j < slices; j++) {
                glBegin(GL_QUADS);

                {
                    glColor3f(color, color, color);
                    color = 1 - color;

                    glVertex3f(points[i][j].x, points[i][j].y, center. z + points[i][j].z);
                    glVertex3f(points[i][j + 1].x, points[i][j + 1].y, center. z + points[i][j + 1].z);
                    glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, center. z + points[i + 1][j + 1].z);
                    glVertex3f(points[i + 1][j].x, points[i + 1][j].y, center. z + points[i + 1][j].z);
                }

                glEnd();
            }
        }
    }
    
    void drawBarrel() {
        Vector points[stacks + 1][slices + 1];
        int i, j;
        double h, r;

        for (i = 0; i <= stacks; i++) {
            h = barrelLength * sin(((double) i / (double) stacks) * (pi / 2));
            r = barrelRadius;
            for (j = 0; j <= slices; j++) {
                double angle = ((double) j / (double) slices) * 2 * pi;
                points[i][j].x = r * cos(angle) + center.x;
                points[i][j].y = r * sin(angle) + center.y;
                points[i][j].z = h;
                points[i][j] = points[i][j].rotate(qw.axis, qw.angleDegrees);
                points[i][j] = points[i][j].rotate(er.axis, er.angleDegrees);
            }
        }

        int color = 0;
        for (i = 0; i < stacks; i++) {
            for (j = 0; j < slices; j++) {
                glBegin(GL_QUADS);

                {
                    glColor3f(color, color, color);
                    color = 1 - color;

                    glVertex3f(points[i][j].x, points[i][j].y, center. z + points[i][j].z);
                    glVertex3f(points[i][j + 1].x, points[i][j + 1].y, center. z + points[i][j + 1].z);
                    glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, center. z + points[i + 1][j + 1].z);
                    glVertex3f(points[i + 1][j].x, points[i + 1][j].y, center. z + points[i + 1][j].z);
                }

                glEnd();
            }
        }
    }
};
