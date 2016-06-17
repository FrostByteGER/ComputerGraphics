#include "PhysicsObject.h"
#include <iostream>

//TODO:Replace maybe

PhysicsObject::PhysicsObject()
{

}

double PhysicsObject::getX() const
{
	return x;
}

void PhysicsObject::setX(const double value)
{
	x = value;
}

double PhysicsObject::getY() const
{
	return y;
}

void PhysicsObject::setY(const double value)
{
	y = value;
}

double PhysicsObject::getZ() const
{
	return z;
}

void PhysicsObject::setZ(const double value)
{
	z = value;
}

double PhysicsObject::getVelocityX() const
{
	return velocityX;
}

void PhysicsObject::setVelocityX(const double value)
{
	velocityX = value;
}

double PhysicsObject::getVelocityY() const
{
	return velocityY;
}

void PhysicsObject::setVelocityY(const double value)
{
	velocityY = value;
}

double PhysicsObject::getVelocityZ() const
{
	return velocityZ;
}

void PhysicsObject::setVelocityZ(const double value)
{
	velocityZ = value;
}

double PhysicsObject::getMass() const
{
	return mass;
}

void PhysicsObject::setMass(const double value)
{
	mass = value;
}
