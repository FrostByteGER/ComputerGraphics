#pragma once

#include <QVector3D>
#include "Transform3D.h"


class Model;

class PhysicsObject
{
	public:

		PhysicsObject(Model* parent, Transform3D* parentTransform);
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
		double getRemainingEnergy() const;
		void setRemainingEnergy(const double value);
        bool getIsMovable() const;
        void setIsMovable(const bool value);
        int getID() const;
        void setID(const int value);

	private:
		Model* parent;
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		Transform3D* transform;

		double velocityX = 0.0;
		double velocityY = 0.0;
		double velocityZ = 0.0;
		QVector3D velocity;

		double mass = 1.0;

		double remainingEnergy = 0.94868329805;

		bool isMovable = true;

        int ID = -1;


};

class PhysicsBox : public PhysicsObject
{
    public:
		PhysicsBox(Model* parent, Transform3D* parentTransform);
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
        double maxX = 1;
        double maxY = 1;
        double maxZ = 1;

        double minX = -1;
        double minY = -1;
        double minZ = -1;

        // 0,-10,-5
        // -0.5
};

class PhysicsSphere : public PhysicsObject
{
    public:
		PhysicsSphere(Model* parent, Transform3D* parentTransform);
		~PhysicsSphere();

        double getSize() const;
        void setSize(double value);

    private:
		double size = 1.0;
};
