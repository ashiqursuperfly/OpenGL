//
// Created by ashiq on 7/2/21.
//

#ifndef OFFLINE3_1605103_RAY_TRACING_H
#define OFFLINE3_1605103_RAY_TRACING_H

#endif //OFFLINE3_1605103_RAY_TRACING_H


#include "1605103_camera.h"
#include "1605103_objects.h"
#include "bitmap_image.hpp"
#include <vector>

class Ray {
public:
    Vector startVector;
    Vector directionUnitVector;
    double t_value;
    Color color;


    Ray() {
        t_value = -1;
    }

    Ray(const Vector &start, const Vector &direction) {
        startVector = start;
        directionUnitVector = direction;
        t_value = -1;
    }
};

class RayTracing {
public:

    Scene & scene;

    RayTracing(Scene &sc) : scene(sc) {}

    Ray intersectAndIlluminate(Ray ray, int recursionLevel, Object * object) const{
        Ray ret;
        Color finalColor;
        Vector intersectionPoint;

        ret.t_value = getIntersectionParameterT(ray, object);
        intersectionPoint = ray.startVector + ray.directionUnitVector * ret.t_value;

        ret.color = object->getColor(intersectionPoint) * object->getAmbient(); // todo: object->color might not do it for floor

        if (ret.t_value < 0) return ret;
        if (recursionLevel < 1) return ret;

        finalColor = Illuminate(ray, intersectionPoint, ret.t_value, recursionLevel, object);
        ret.color = finalColor;

        return ret;
    }

    Color Illuminate(Ray mainRay, Vector IntersectionPoint, double ParameterT, int reflectionLevel, Object * object) const{
        Color resultColor = object->getColor(IntersectionPoint) * object->getAmbient(); // todo: object->color might not do it for floor

        Vector normalAtIntersectionPoint = object->getNormal(IntersectionPoint);

        double dotValue = normalAtIntersectionPoint.dot(mainRay.directionUnitVector);
        if (dotValue > 0) {
            normalAtIntersectionPoint = normalAtIntersectionPoint * (-1.0);
        }

        for (auto &Light : scene.lights) {
            Vector lightRayDirection = Light.position - IntersectionPoint;
            double lightToThisObjectDistance = lightRayDirection.absoluteValue();
            lightRayDirection = lightRayDirection.normalize();

            Vector lightRayStart = IntersectionPoint + lightRayDirection * 1;
            Ray lightRayTowardsThisObject(lightRayStart, lightRayDirection);

            bool interceptedByAnotherObjectBefore = false;

            for (int i=0; i < scene.numObjects; i++) {
                Ray interceptionResult = intersectAndIlluminate(lightRayTowardsThisObject, 0, scene.objects[i]);
                if (interceptionResult.t_value > 0 && interceptionResult.t_value < lightToThisObjectDistance) {
                    interceptedByAnotherObjectBefore = true;
                    break;
                }
            }

            if (!interceptedByAnotherObjectBefore) {
                double lightFactor = 1;
                double lambert = std::max(lightRayDirection.dot(normalAtIntersectionPoint), 0.0);
                Vector R = normalAtIntersectionPoint * 2.0 * lightRayDirection.dot(normalAtIntersectionPoint) - lightRayDirection; // R = 2(L.N)N-L;
                double Phong = std::max(mainRay.directionUnitVector.dot(R), 0.0);
                resultColor = resultColor + object->getColor(IntersectionPoint) * (lightFactor * lambert * object->getDiffuse()); // todo: object->color might not do it for floor

                resultColor = resultColor + Light.color * (lightFactor * pow(Phong, object->getShine()) * object->getSpecular());
            }
        }
        if (reflectionLevel > 0) {
            Vector reflectionRayDirection = getReflectedVectorDirection(mainRay.directionUnitVector, normalAtIntersectionPoint);

            Vector reflectedRayStart = IntersectionPoint + reflectionRayDirection * 1;
            Ray reflectedRay(reflectedRayStart, reflectionRayDirection);

            int minimumObstacleIndex = INT32_MIN;
            minimumObstacleIndex = getMinimumObstacleIdx(reflectedRay, minimumObstacleIndex);

            if (minimumObstacleIndex != INT32_MIN) {
                Ray nextLevel = intersectAndIlluminate(reflectedRay, reflectionLevel - 1, scene.objects[minimumObstacleIndex]);
                resultColor = resultColor + nextLevel.color * 1.0 * object->getReflection();
            }
        }
        return resultColor;
    }

    int getMinimumObstacleIdx(const Ray &reflectedRay, int minimumObstacleIndex) const {

        minimumObstacleIndex = INT32_MIN;
        double minimumValueOfParameterT = INT32_MAX;

        for (int i = 0; i < scene.numObjects; i++) {
            Object * obj = scene.objects[i];

            Ray intersectOrNot = intersectAndIlluminate(reflectedRay, 0, obj);

            if (intersectOrNot.t_value > 0 && intersectOrNot.t_value < minimumValueOfParameterT) {
                minimumObstacleIndex = i;
                minimumValueOfParameterT = intersectOrNot.t_value;
            }
        }
        return minimumObstacleIndex;
    }

    static Vector getReflectedVectorDirection(Vector mainRay, Vector Normal) {
        Vector reflectionRay = mainRay - Normal * (2.0 * mainRay.dot(Normal));
        reflectionRay = reflectionRay.normalize();
        return reflectionRay;
    }

    static double getIntersectionParameterT(Ray & ray, Object * object) {
        if (object->name == "sphere") {
            auto s = dynamic_cast<Sphere *>(object);
            double a, b, c, d, tem, t, t1, t2, r;
            Vector R0, Rd;

            r = s->radius;
            R0 = ray.startVector - s->reference_point;
            Rd = ray.directionUnitVector;

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
        else if (object->name == "floor") {
            return -(ray.startVector.z / ray.directionUnitVector.z);
        }
        return 0.0;
    }

};


class RayTracingCapturer {
    RayTracing rayTracing;
public:
    Scene & scene;

    RayTracingCapturer(Scene &sc) : scene(sc), rayTracing(sc) {}

    void capture(double windowWidth, double windowHeight, double imageWidth, double imageHeight, const Camera & camera) const {
        std::vector<std::vector<Color>> imagePixels;

        double planeDistanceFromCamera = (windowHeight / 2.0) / tan(camera.fovy / 2.0 * (pi / 180.0));

        Vector dx, dy, dz;
        dy = camera.l * planeDistanceFromCamera;
        dx = camera.r * (windowWidth / 2.0);
        dz = camera.u * (windowHeight / 2.0);

        Vector topLeftCornerOfWholeFrame = camera.pos + dy - dx + dz;

        double changeThroughRow = (windowWidth * 1.0) / imageWidth;
        double changeThroughColumn = (windowHeight * 1.0) / imageHeight;

        Vector currLeftCorner, eyeToPixelDirection, eyeToPixelRayStart;
        for (int i = 0; i < imageHeight; i++) {
            imagePixels.emplace_back();

            for (int j = 0; j < imageWidth; j++) {
                currLeftCorner = topLeftCornerOfWholeFrame + camera.r * (j * changeThroughRow) - camera.u * (i * changeThroughColumn);

                eyeToPixelDirection = currLeftCorner - camera.pos;
                eyeToPixelDirection = eyeToPixelDirection.normalize();
                eyeToPixelRayStart = camera.pos;

                Ray eyeToPixelRay(eyeToPixelRayStart, eyeToPixelDirection);

                imagePixels[i].push_back(getPixelColor(eyeToPixelRay));
            }
        }

        populatePixelsWithColor(imageWidth, imageHeight, imagePixels);
    }


    Color getPixelColor(const Ray &mainRay) const {
        Color resultColor(0, 0, 0);
        int closestObstacleIndex = INT32_MIN;
        double minimumValueOfParameterT = INT32_MAX;

        for (int i = 0; i < scene.numObjects; i++) {
            Ray intersectOrNot = rayTracing.intersectAndIlluminate(mainRay, 0, scene.objects[i]);
            if (intersectOrNot.t_value > 0 && intersectOrNot.t_value < minimumValueOfParameterT) {
                closestObstacleIndex = i;
                minimumValueOfParameterT = intersectOrNot.t_value;
            }
        }
        if (closestObstacleIndex != INT32_MIN) {
            Ray finalRayAfterAllLevelReflections = rayTracing.intersectAndIlluminate(mainRay, scene.recursionLevels, scene.objects[closestObstacleIndex]);
            resultColor = finalRayAfterAllLevelReflections.color;
        }
        return resultColor;
    }

    static void populatePixelsWithColor(double imageWidth, double imageHeight, const std::vector<std::vector<Color>> &frame) {
        bitmap_image image(static_cast<const unsigned int>(imageWidth), static_cast<const unsigned int>(imageHeight));
        for (int i = 0; i < imageHeight; i++) {
            for (int j = 0; j < imageWidth; j++) {
                int r = frame[i][j].r * 255;
                int g = frame[i][j].g * 255;
                int b = frame[i][j].b * 255;
                if(r < 0) r = 0;
                if(r > 255) r = 255;

                if(g < 0) g = 0;
                if(g > 255) g = 255;

                if(b < 0) b = 0;
                if(b > 255) b = 255;
                image.set_pixel(i, j, r, g, b);
            }
        }
        image.save_image("1605103.bmp");
    }
};