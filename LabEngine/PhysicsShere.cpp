#include "PhysicsObject.h"

PhysicsShere::PhysicsShere()
{
    type = 2;
}
double PhysicsShere::getSize() const{
    return size;
};

void PhysicsShere::setSize(double value)
{
    size = value;
};
