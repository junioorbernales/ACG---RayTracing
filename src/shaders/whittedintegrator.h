#ifndef WHITTEDINTEGRATOR_H
#define WHITTEDINTEGRATOR_H

#include "shader.h"

class Shape;
class LightSource;

class WhittedIntegrator : public Shader
{
public:
    WhittedIntegrator();
    WhittedIntegrator(Vector3D color_, double maxDist_, Vector3D bgColor_);

    Vector3D computeColor(const Ray& r,
        const std::vector<Shape*>& objList,
        const std::vector<LightSource*>& lsList) const;

private:
    double maxDist;
    Vector3D color;

    Vector3D computeDirectIllumination(
        const Ray& r,
        const std::vector<Shape*>& objList,
        const std::vector<LightSource*>& lsList) const;
};

#endif // WHITTEDINTEGRATOR_H