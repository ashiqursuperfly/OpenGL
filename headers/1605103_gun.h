//
// Created by ashiq on 3/17/21.
//

#ifndef OFFLINE1_GUN_H
#define OFFLINE1_GUN_H

#endif //OFFLINE1_GUN_H

class Gun {
private:
    int stacks = 200;
    int slices = 90;
    float barrelRadius = 6.0;
    float barrelLength = 80.0;
    float tipInnerRadius = barrelRadius * 0.2f;
    float tipOutRadius = barrelRadius * 1.5f;
    float tipLength = barrelLength;
    float barrelBaseLength = barrelLength * 0.2f;
    float baseSphereRadius = barrelRadius * 3.0f;

    Vector bullets[100];
    int bulletsUsed = 0;

    Vector center = Vector();
    Vector initialGunPoint = Vector(0, 0, barrelLength);
    Vector gunPoint = Vector(0, 0, barrelLength);


    void drawBullets() {

        float bulletWidth = 3.0;

        for (int i = 0; i < bulletsUsed; ++i) {
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_QUADS);
            {
                Vector b = bullets[i];
                glVertex3f(b.x - bulletWidth, b.y - bulletWidth, b.z - 5);
                glVertex3f(b.x - bulletWidth, b.y + bulletWidth, b.z - 5);

                glVertex3f(b.x + bulletWidth, b.y - bulletWidth, b.z - 5);
                glVertex3f(b.x + bulletWidth, b.y + bulletWidth, b.z - 5);


                glVertex3f(b.x - bulletWidth, b.y + bulletWidth, b.z - 5);
                glVertex3f(b.x + bulletWidth, b.y + bulletWidth, b.z - 5);

                glVertex3f(b.x - bulletWidth, b.y - bulletWidth, b.z - 5);
                glVertex3f(b.x + bulletWidth, b.y - bulletWidth, b.z - 5);

            }
            glEnd();
        }
    }

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
                points[i][j] = points[i][j].rotate(as.axis, as.angleDegrees);
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

                    if (points[i][j].z < barrelBaseLength || points[i + 1][j].z < barrelBaseLength || points[i][j + 1].z < barrelBaseLength || points[i+1][j+1].z < barrelBaseLength ){
                        continue;
                    }

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

        int baseStacks = (int) ((barrelBaseLength * (float)stacks) / barrelLength);

        for (i = 0; i <= stacks; i++) {
            h = barrelLength * sin(((double) i / (double) stacks) * (pi / 2));
            r = barrelRadius;

            for (j = 0; j <= slices; j++) {
                double angle = ((double) j / (double) slices) * 2 * pi;
                angle += df.angleDegrees;

                if (i < baseStacks) {
//                    float baseRatio = barrelBaseLength / barrelLength;
//                    float baseStacks = stacks * baseRatio;
                    h = barrelBaseLength * sin(((double) i / (double) baseStacks) * (pi / 2));
                    r = barrelRadius * cos(((double) i / (double) baseStacks) * (pi / 2));
                }

                points[i][j].x = r * cos(angle) + center.x;
                points[i][j].y = r * sin(angle) + center.y;
                points[i][j].z = h;

                if (i < baseStacks) {
                    points[i][j] = points[i][j].rotate(Vector(0,0,1), 180) + Vector(0, 0, barrelBaseLength * 1.6);
                }

                points[i][j] = points[i][j].rotate(qw.axis, qw.angleDegrees);
                points[i][j] = points[i][j].rotate(er.axis, er.angleDegrees);
                points[i][j] = points[i][j].rotate(as.axis, as.angleDegrees);
            }
        }

        int color = 0;
        int colorAlternate = 1;
        for (i = 0; i < stacks; i++) {
            for (j = 0; j < slices; j++) {
                glBegin(GL_QUADS);
                {
                    if (i >= baseStacks){
                        glColor3f(color, color, color);
                    }
                    else glColor3f(colorAlternate, colorAlternate, colorAlternate);

                    color = 1 - color;
                    colorAlternate = 1 - colorAlternate;

                    glVertex3f(points[i][j].x, points[i][j].y, center. z + points[i][j].z);
                    glVertex3f(points[i][j + 1].x, points[i][j + 1].y, center. z + points[i][j + 1].z);
                    glVertex3f(points[i + 1][j + 1].x, points[i + 1][j + 1].y, center. z + points[i + 1][j + 1].z);
                    glVertex3f(points[i + 1][j].x, points[i + 1][j].y, center. z + points[i + 1][j].z);
                }
                glEnd();
            }
        }
    }

    void drawBase() {

        Vector points[stacks + 1][slices + 1];
        int i, j;
        double h, r;

        //generate points
        for (i = 0; i <= stacks; i++) {
            h = baseSphereRadius * sin(((double) i / (double) stacks) * (pi / 2));
            r = baseSphereRadius * cos(((double) i / (double) stacks) * (pi / 2));
            for (j = 0; j <= slices; j++) {
                double angle = ((double) j / (double) slices) * 2 * pi;
                points[i][j].x = r * cos(angle) + center.x;
                points[i][j].y = r * sin(angle) + center.y;
                points[i][j].z = h;
                points[i][j] = points[i][j].rotate(er.axis, er.angleDegrees);
            }
        }

        Vector centerSphere = Vector(center.x, center.y, center.z - 5);

        int color = 0;
        //draw quads using generated points
        for (i = 0; i < stacks; i++) {
            // glColor3f((double) i / (double) stacks, (double) i / (double) stacks, (double) i / (double) stacks);
            for (j = 0; j < slices; j++) {
                glBegin(GL_QUADS);

                {
                    glColor3f(color, color, color);
                    color = 1 - color;
                    //upper hemisphere
                    Vector p1 = points[i][j].rotate(qw.axis, qw.angleDegrees);
                    Vector p2 = points[i][j + 1].rotate(qw.axis, qw.angleDegrees);
                    Vector p3 = points[i + 1][j + 1].rotate(qw.axis, qw.angleDegrees);
                    Vector p4 = points[i + 1][j].rotate(qw.axis, qw.angleDegrees);
                    glVertex3f(p1.x, p1.y, centerSphere. z + p1.z);
                    glVertex3f(p2.x, p2.y, centerSphere. z + p2.z);
                    glVertex3f(p3.x, p3.y, centerSphere. z + p3.z);
                    glVertex3f(p4.x, p4.y, centerSphere. z + p4.z);
                    //lower hemisphere
                    p1 = points[i][j].rotate(qw.axis, 360 - qw.angleDegrees);
                    p2 = points[i][j + 1].rotate(qw.axis, 360 - qw.angleDegrees);
                    p3 = points[i + 1][j + 1].rotate(qw.axis, 360 - qw.angleDegrees);
                    p4 = points[i + 1][j].rotate(qw.axis, 360 - qw.angleDegrees);
                    glVertex3f(p1.x, p1.y, centerSphere. z - p1.z);
                    glVertex3f(p2.x, p2.y, centerSphere. z - p2.z);
                    glVertex3f(p3.x, p3.y, centerSphere. z - p3.z);
                    glVertex3f(p4.x, p4.y, centerSphere. z - p4.z);
                }

                glEnd();
            }
        }
    }

public:
    Rotation qw = Rotation(Vector(1, 0, 0), 0, 45);
    Rotation as = Rotation(Vector(0, 1, 0), 0, 45);
    Rotation er = Rotation(Vector(0, 1, 0), 0, 45);
    Rotation df = Rotation(Vector(0, 0, 0), 0, 45);

    Vector & getBullet(int idx) {
        return bullets[idx];
    }

    void setBullet(int idx, Vector & updated) {
        bullets[idx] = updated;
    }

    void updateGunPoint() {
        gunPoint = initialGunPoint.rotate(qw.axis, qw.angleDegrees);
        gunPoint = gunPoint.rotate(er.axis, er.angleDegrees);
        gunPoint = gunPoint.rotate(as.axis, as.angleDegrees);
        std::cout<<"GunPoint:";
        gunPoint.print();
        std::cout<<"\n";
    }

    void shoot(const Vector & target) {
        Vector pointingVector = gunPoint - center;

        double ratio = std::abs(target.z / pointingVector.z);

        Vector bulletFinalPoint = pointingVector * ratio;

        if (bulletFinalPoint.x >= -target.x && bulletFinalPoint.x <= target.x) {
            if (bulletFinalPoint.y >= -target.y && bulletFinalPoint.y <= target.y) {
                bullets[bulletsUsed] = bulletFinalPoint;

                std::cout<<"Hit Target:";
                bulletFinalPoint.print();
                std::cout<<"\n";

                bulletsUsed++;
            }
        }

    }

    void draw() {
        drawTip();
        drawBarrel();
        drawBase();
        drawBullets();
    }


};
