#include "PhysicsObject.h"

PhysicsSphere::PhysicsSphere()
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
