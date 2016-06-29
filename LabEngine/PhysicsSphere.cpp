#include "PhysicsObject.h"
#include <QDebug>

PhysicsSphere::PhysicsSphere(PhysicsThread* parentSimulation, Model* parent, Transform3D* parentTransform) : PhysicsObject(parentSimulation, parent, parentTransform)
{
}

PhysicsSphere::~PhysicsSphere()
{
	parentSimulation->deregisterPhysicsSphere(this);
	qDebug() << "DELETING COLLIDER";
}
double PhysicsSphere::getSize() const{
    return size;
}

void PhysicsSphere::setSize(double value)
{
	size = value;
}

void PhysicsSphere::addVelocity(const float& x, const float& y, const float& z)
{
	velocityToAdd = QVector3D(x,y,z);
	qDebug() << "ADD" << velocityToAdd;
}
