#include "PhysicsObject.h"
#include <iostream>

PhysicsObject::PhysicsObject(Model* parent, VTransform* parentTransform) : parent(parent), transform(parentTransform)
{
}

PhysicsObject::~PhysicsObject()
{

}

double PhysicsObject::getX() const
{
	return transform->translation().x();
	//return x;
}

void PhysicsObject::setX(const double value)
{
	transform->setTranslationX(value);
	x = value;
}

double PhysicsObject::getY() const
{
	return transform->translation().y();
	//return y;
}

void PhysicsObject::setY(const double value)
{
	transform->setTranslationY(value);
	y = value;
}

double PhysicsObject::getZ() const
{
	return transform->translation().z();
	//return z;
}

void PhysicsObject::setZ(const double value)
{
	transform->setTranslationZ(value);
	z = value;
}

QVector3D PhysicsObject::getPosition() const
{
	return transform->translation();
}

void PhysicsObject::setPosition(const QVector3D& position)
{
	transform->setTranslation(position);
}

void PhysicsObject::setPosition(const float& x, const float& y, const float& z)
{
	transform->setTranslation(x,y,z);
}

double PhysicsObject::getVelocityX() const
{
	return velocity.x();
	//return velocityX;
}

void PhysicsObject::setVelocityX(const double value)
{
	velocity.setX(value);
	velocityX = value;
}

double PhysicsObject::getVelocityY() const
{
	return velocity.y();
	//return velocityY;
}

void PhysicsObject::setVelocityY(const double value)
{
	velocity.setY(value);
	velocityY = value;
}

double PhysicsObject::getVelocityZ() const
{
	return velocity.z();
	//return velocityZ;
}

void PhysicsObject::setVelocityZ(const double value)
{
	velocity.setZ(value);
	velocityZ = value;
}

QVector3D PhysicsObject::getVelocity() const
{
	return velocity;
}

void PhysicsObject::setVelocity(const QVector3D& velocity)
{
	this->velocity = velocity;
}

void PhysicsObject::setVelocity(const float& x, const float& y, const float& z)
{
	velocity.setX(x);
	velocity.setY(y);
	velocity.setZ(z);
}

double PhysicsObject::getMass() const
{
	return mass;
}

void PhysicsObject::setMass(const double value)
{
	mass = value;
}

bool PhysicsObject::getIsMovable() const
{
    return isMovable;
}

void PhysicsObject::setIsMovable(bool value)
{
    isMovable = value;
}

double PhysicsObject::getRemainingEnergy() const{
	return remainingEnergy;
}

void PhysicsObject::setRemainingEnergy(const double value){
	remainingEnergy = value;
}

int PhysicsObject::getID() const{
    return ID;
};

void PhysicsObject::setID(const int value){
    ID = value;
};

double PhysicsObject::getHorizontalFriction() const{
    return horizontalFriction;
};
void PhysicsObject::setHorizontalFriction(const double value)
{
    horizontalFriction = value;
};

double PhysicsObject::getVerticalFriction() const{
    return verticalFriction;
};
void PhysicsObject::setVerticalFriction(const double value)
{
    verticalFriction = value;
};
