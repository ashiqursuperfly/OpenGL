//
// Created by ashiq on 7/2/21.
//

#ifndef OFFLINE3_1605103_RAY_TRACING_H
#define OFFLINE3_1605103_RAY_TRACING_H

#endif //OFFLINE3_1605103_RAY_TRACING_H

#define MIN_OBSTACLE_DIST (-50)
#define MAX_OBSTACLE_DIST INT32_MAX

#include "1605103_camera.h"
#include "1605103_objects.h"
#include "bitmap_image.hpp"
#include <vector>

class Ray {
public:
    Vector start;
    Vector dir;
    double t;
    Color color;


    Ray() {
        t = -1;
    }

    Ray(const Vector &startVector, const Vector &direction) {
        start = startVector;
        dir = direction;
        t = -1;
    }

    bool isIntersect(double minValOfParamT) const {
        if (t > 0 && t < minValOfParamT) {
            return true;
        }
        return false;
    }
};

class RayTracing {
public:

    Scene & scene;

    RayTracing(Scene &sc) : scene(sc) {}

    Ray intersect(Ray ray, int recursionLevel, Object * object) const{
        Ray ret;
        Color finalColor;
        Vector intersectionPoint;

        ret.t = getIntersectionParameterT(ray, object);
        intersectionPoint = ray.start + ray.dir * ret.t;

        ret.color = object->getColor(intersectionPoint) * object->getAmbient();

        if (ret.t < 0) return ret;
        if (recursionLevel < 1) return ret;

        finalColor = phongLighting(ray, intersectionPoint, recursionLevel, object);
        ret.color = finalColor;

        return ret;
    }

    //TODO:
    Color phongLighting(Ray mainRay, Vector intersectionPoint, int reflectionLevel, Object *object) const {
        Color resultColor = object->getColor(intersectionPoint) * object->getAmbient();

        Vector normalAtIntersectionPoint = object->getNormal(intersectionPoint);

        double dotValue = normalAtIntersectionPoint.dot(mainRay.dir);
        if (dotValue > 0) {
            normalAtIntersectionPoint = normalAtIntersectionPoint * (-1.0);
        }

        for (auto &Light : scene.lights) {
            Vector lightRayDirection = Light.position - intersectionPoint;
            double lightToThisObjectDistance = lightRayDirection.absoluteValue();
            lightRayDirection = lightRayDirection.normalize();

            Vector lightRayStart = intersectionPoint + lightRayDirection * 1;
            Ray lightRayTowardsThisObject(lightRayStart, lightRayDirection);

            bool interceptedByAnotherObjectBefore = false;

            for (int i=0; i < scene.numObjects; i++) {
                Ray interceptionResult = intersect(lightRayTowardsThisObject, 0, scene.objects[i]);
                if (interceptionResult.t > 0 && interceptionResult.t < lightToThisObjectDistance) {
                    interceptedByAnotherObjectBefore = true;
                    break;
                }
            }

            if (!interceptedByAnotherObjectBefore) {
                double lightFactor = 1;
                double lambertValue = std::max(lightRayDirection.dot(normalAtIntersectionPoint), 0.0);
                Vector R = normalAtIntersectionPoint * 2.0 * lightRayDirection.dot(normalAtIntersectionPoint) - lightRayDirection; // R = 2(L.N)N-L;
                double phongValue = std::max(mainRay.dir.dot(R), 0.0);
                resultColor = resultColor + object->getColor(intersectionPoint) * (lightFactor * lambertValue * object->getDiffuse());

                resultColor = resultColor + Light.color * (lightFactor * pow(phongValue, object->getShine()) * object->getSpecular());
            }
        }
        if (reflectionLevel > 0) {
            Vector reflectionRayDirection = mainRay.dir.reflection(normalAtIntersectionPoint);

            Vector reflectedRayStart = intersectionPoint + reflectionRayDirection;
            Ray reflectedRay(reflectedRayStart, reflectionRayDirection);

            int closestObstacleIdx = getClosestObstacleIdx(reflectedRay);

            if (closestObstacleIdx != MIN_OBSTACLE_DIST) {
                Ray nextLevel = intersect(reflectedRay, reflectionLevel - 1, scene.objects[closestObstacleIdx]);
                resultColor = resultColor + nextLevel.color * 1.0 * object->getReflection();
            }
        }
        return resultColor;
    }

    int getClosestObstacleIdx(const Ray &ray) const {

        int closestObstacleObjectID = MIN_OBSTACLE_DIST;
        double minParamT = MAX_OBSTACLE_DIST;

        for (int objectID = 0; objectID < scene.numObjects; objectID++) {
            Object * obj = scene.objects[objectID];

            Ray intersectRay = intersect(ray, 0, obj);

            if (intersectRay.isIntersect(minParamT)) {
                closestObstacleObjectID = objectID;
                minParamT = intersectRay.t;
            }
        }
        return closestObstacleObjectID;
    }

    // TODO:
    static double getIntersectionParameterT(Ray & ray, Object * object) {
        if (object->name == "floor") {
            return -(ray.start.z / ray.dir.z);
        }
        else if (object->name == "sphere") {
            auto s = dynamic_cast<Sphere *>(object);
            double a, b, c, d, tem, t, t1, t2, r;
            Vector R0, Rd;

            r = s->radius;
            R0 = ray.start - s->reference_point;
            Rd = ray.dir;

            a = Rd.dot(Rd);
            b = 2.0 * Rd.dot(R0);
            c = R0.dot(R0) - r * r;

            tem = b * b - 4.0 * a * c;

            if (tem < 0) {
                t = -1.0;
            } else {
                d = sqrt(tem);
                t1 = (-b + d) / (2.0 * a);
                t2 = (-b - d) / (2.0 * a);

                if (t1 >= 0 && t2 >= 0) {
                    t = std::min(t1, t2);
                } else {
                    t = std::max(t1, t2);
                }
            }

            return t;
        }
        return 0.0;
    }

};


class RayTracingCapturer {
    RayTracing rayTracing;
public:
    Scene & scene;

    RayTracingCapturer(Scene &sc) : scene(sc), rayTracing(sc) {}

    void capture(const std::string & filename, double windowWidth, double windowHeight, double imageWidth, double imageHeight, const Camera & camera) const {
        std::vector<std::vector<Color>> imagePixels;

        double planeDistance = (windowHeight / 2.0) / tan(camera.fovy / 2.0 * (pi / 180.0));

        Vector frameTopLeft = camera.pos + (camera.l * planeDistance) - (camera.r * (windowWidth / 2.0)) + (camera.u * (windowHeight / 2.0));

        double du = (windowWidth * 1.0) / imageWidth;
        double dv = (windowHeight * 1.0) / imageHeight;

        for (int i = 0; i < imageHeight; i++) {
            imagePixels.emplace_back();

            for (int j = 0; j < imageWidth; j++) {
                Vector currentTopLeft = frameTopLeft + camera.r * (j * du) - camera.u * (i * dv);

                Vector cameraToPixelDir = (currentTopLeft - camera.pos).normalize();
                Ray cameraToPixelRay(camera.pos, cameraToPixelDir);

                imagePixels[i].push_back(getPixelColor(cameraToPixelRay));
            }
        }

        generateBitmap(filename, imageWidth, imageHeight, imagePixels);
    }

    Color getPixelColor(const Ray &mainRay) const {
        int closestObstacleID = MIN_OBSTACLE_DIST;
        double minParamT = MAX_OBSTACLE_DIST;

        for (int objectID = 0; objectID < scene.numObjects; objectID++) {
            Ray intersectRay = rayTracing.intersect(mainRay, 0, scene.objects[objectID]);
            if (intersectRay.isIntersect(minParamT)) {
                closestObstacleID = objectID;
                minParamT = intersectRay.t;
            }
        }
        if (closestObstacleID != MIN_OBSTACLE_DIST) {
            Ray intersectRayRecursive = rayTracing.intersect(mainRay, scene.recursionLevels, scene.objects[closestObstacleID]);
            return intersectRayRecursive.color;
        }
        return {0, 0, 0};
    }

    static void generateBitmap(const std::string & filename, double imageWidth, double imageHeight, const std::vector<std::vector<Color>> &frame) {
        bitmap_image image((unsigned int)imageWidth, (unsigned int)imageHeight);
        for (int i = 0; i < imageHeight; i++) {
            for (int j = 0; j < imageWidth; j++) {

                double r = std::min(255.0, std::max(0.0, frame[i][j].r * 255));
                double g = std::min(255.0, std::max(0.0, frame[i][j].g * 255));
                double b = std::min(255.0, std::max(0.0, frame[i][j].b * 255));

                image.set_pixel(j, i, r, g, b);
            }
        }
        image.save_image(filename);
    }
};