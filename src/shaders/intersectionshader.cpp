#include "intersectionshader.h"
#include "../core/utils.h"

IntersectionShader::IntersectionShader() :
    hitColor(Vector3D(1, 0, 0))
{ }

IntersectionShader::IntersectionShader(Vector3D hitColor_, Vector3D bgColor_) :
    Shader(bgColor_), hitColor(hitColor_)
{ }

Vector3D IntersectionShader::computeColor(const Ray& r, const std::vector<Shape*>& objList, const std::vector<LightSource*>& lsList) const
{
    //(FILL..)
    //We need to iterate for every object in the scene to find if it intersects any ray.
    if (Utils::hasIntersection(r, objList))
    {
        return Vector3D(1.0, 0.0, 0.0);
    }

    //If the ray doesn't hit any object
    return bgColor;
}
