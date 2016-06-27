#include "PhysicsObject.h"

PhysicsSphere::PhysicsSphere(Model* parent, Transform3D* parentTransform) : PhysicsObject(parent, parentTransform)
{
}

PhysicsSphere::~PhysicsSphere()
{

}
double PhysicsSphere::getSize() const{
    return size;
}

void PhysicsSphere::setSize(double value)
{
    size = value;
}
