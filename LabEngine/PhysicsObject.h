#pragma once

#include <QVector3D>
#include "Transform3D.h"

class PhysicsObject
{
	public:

		PhysicsObject();
		~PhysicsObject();

		double getX() const;
		void setX(const double value);
		double getY() const;
		void setY(const double value);
		double getZ() const;
		void setZ(const double value);
		QVector3D getPosition() const;
		void setPosition(const QVector3D& position);
		void setPosition(const float& x, const float& y, const float& z);

		double getVelocityX() const;
		void setVelocityX(const double value);
		double getVelocityY() const;
		void setVelocityY(const double value);
		double getVelocityZ() const;
		void setVelocityZ(const double value);
		QVector3D getVelocity() const;
		void setVelocity(const QVector3D& velocity);
		void setVelocity(const float& x, const float& y, const float& z);

		double getMass() const;
		void setMass(const double value);
		double getCollideCounter() const;
		void setCollideCounter(const double value);
        double getFriction() const;
        void setFriction(const double value);
        bool getIsMovable() const;
        void setIsMovable(bool value);

	private:
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		Transform3D transform;

		double velocityX = 0.0;
		double velocityY = 0.0;
		double velocityZ = 0.0;
		QVector3D velocity;

		double mass = 1.0;

        double friction = 0.94868329805;

        bool isMovable = false;


};

class PhysicsBox : public PhysicsObject
{
    public:
        PhysicsBox();
		~PhysicsBox();

        double getMaxX() const;
        void setMaxX(double value);

        double getMaxY() const;
        void setMaxY(double value);

        double getMaxZ() const;
        void setMaxZ(double value);

        double getMinX() const;
        void setMinX(double value);

        double getMinY() const;
        void setMinY(double value);

        double getMinZ() const;
        void setMinZ(double value);

    private:
        double maxX = 0;
        double maxY = 0;
        double maxZ = 0;

        double minX = 0;
        double minY = 0;
        double minZ = 0;
};

class PhysicsSphere : public PhysicsObject
{
    public:
		PhysicsSphere();
		~PhysicsSphere();

        double getSize() const;
        void setSize(double value);

    private:
        double size = 0;
};
