#include "PhysicsObject.h"

PhysicsBox::PhysicsBox(Model* parent, VTransform* parentTransform) : PhysicsObject(parent, parentTransform)
{

}

PhysicsBox::~PhysicsBox()
{

}

double PhysicsBox::getMaxX() const
{
    return maxX;
}

void PhysicsBox::setMaxX(const double value)
{
    maxX = value;
}

double PhysicsBox::getMaxY() const
{
    return maxY;
}

void PhysicsBox::setMaxY(double value)
{
    maxY = value;
}

double PhysicsBox::getMaxZ() const
{
    return maxZ;
}

void PhysicsBox::setMaxZ(double value)
{
    maxZ = value;
}

double PhysicsBox::getMinX() const
{
    return minX;
}

void PhysicsBox::setMinX(double value)
{
    minX = value;
}

double PhysicsBox::getMinY() const
{
    return minY;
}

void PhysicsBox::setMinY(double value)
{
    minY = value;
}

double PhysicsBox::getMinZ() const
{
    return minZ;
}

void PhysicsBox::setMinZ(double value)
{
    minZ = value;
}


