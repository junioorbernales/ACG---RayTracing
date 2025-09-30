#include "phong.h"

#include <iostream>
#include <numbers>

Phong::Phong()
{ }

Phong::Phong(Vector3D Kd_, Vector3D Ks_, float alpha_):
rho_d(Kd_), Ks(Ks_), alpha(alpha_){}


Vector3D Phong::getReflectance(const Vector3D& n, const Vector3D& wo,
    const Vector3D& wi) const {

    //(FILL..)
    // Compute ideal reflection direction
    Vector3D wr = 2.0 * (dot(n, wi)) * n - wi;

    // Compute diffuse term: rho_d / pi

    double pi = std::numbers::pi;
    Vector3D diffuse = rho_d * (1.0 / pi);

    // Compute specular term: Ks * (wo . wr)^alpha
    double specAngle = std::max(0.0, dot(wo, wr));
    Vector3D specular = Ks * pow(specAngle, alpha);

    // Return total reflectance
    return diffuse + specular;
};


double Phong::getIndexOfRefraction() const
{
    std::cout << "Warning! Calling \"Material::getIndexOfRefraction()\" for a non-transmissive material"
              << std::endl;

    return -1;
}


Vector3D Phong::getEmissiveRadiance() const
{
    return Vector3D(0.0);
}


Vector3D Phong::getDiffuseReflectance() const
{
    return rho_d;
}

