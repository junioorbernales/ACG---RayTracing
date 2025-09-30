#include "whittedintegrator.h"
#include "../core/utils.h"
#include <iostream>

WhittedIntegrator::WhittedIntegrator() :
    color(Vector3D(1, 0, 0))
{ }

WhittedIntegrator::WhittedIntegrator(Vector3D hitColor_, double maxDist_, Vector3D bgColor_) :
    Shader(bgColor_), maxDist(maxDist_), color(hitColor_)
{ }

Vector3D WhittedIntegrator::computeColor(const Ray& r, const std::vector<Shape*>& objList, const std::vector<LightSource*>& lsList) const
{
    //(FILL..)
    return computeDirectIllumination(r, objList, lsList);
}

Vector3D WhittedIntegrator::computeDirectIllumination(
    const Ray& r,
    const std::vector<Shape*>& objList,
    const std::vector<LightSource*>& lsList) const
{
    // 1. Find nearest intersection
    double tClosest = maxDist;
    const Shape* hitObject = nullptr;
    Vector3D hitNormal;
    Vector3D hitPoint;
   
    for (const auto& obj : objList) {
        double t = (maxDist) - (r.minT);
        Intersection its;
        bool intersect = Utils::getClosestIntersection(r, objList, its);
        if (intersect && t < tClosest) {
            tClosest = t;
            hitObject = obj;
            hitNormal = its.normal;
            hitPoint = its.itsPoint;
        }
    }

    // 2. If no hit, return background color
    if (!(Utils::hasIntersection(r, objList)))
        return bgColor;

    // 3. Direct illumination from point lights
    Vector3D L(0.0, 0.0, 0.0);

    for (const auto& light : lsList) {
        Vector3D wi = (light->sampleLightPosition() - hitPoint).normalized();
        Vector3D lightColor = light->getIntensity();

        // Shadow ray
        Ray shadowRay(hitPoint + hitNormal * 1e-4, wi); // small bias
        bool inShadow = false;

        for (const auto& obj : objList) {
            double t;
            Vector3D n;
            Intersection shadowIts;
            if (Utils::getClosestIntersection(shadowRay, objList, shadowIts)) {
                inShadow = true;
                break;
            }
        }

        if (!inShadow) {
            double ndotl = std::max(0.0, dot(hitNormal, wi));
            L += lightColor * ndotl;
        }
    }

    return L * color;
}