#pragma once

class PhysicsObject
{
	public:

		PhysicsObject();

		double getX() const;
		void setX(const double value);
		double getY() const;
		void setY(const double value);
		double getZ() const;
		void setZ(const double value);
		double getVelocityX() const;
		void setVelocityX(const double value);
		double getVelocityY() const;
		void setVelocityY(const double value);
		double getVelocityZ() const;
		void setVelocityZ(const double value);
		double getMass() const;
		void setMass(const double value);
		double getCollideCounter() const;
		void setCollideCounter(const double value);

	private:
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;

		double velocityX = 0.0;
		double velocityY = 0.0;
		double velocityZ = 0.0;

		double mass = 1.0;

		double collideCounter = 0.0;
};
