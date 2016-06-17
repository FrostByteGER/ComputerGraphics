#pragma once

#include <vector>
#include "PhysicsObject.h"


class PhysicsThread
{
	public:

		PhysicsThread(int minx ,int miny ,int minz ,int maxx ,int maxy ,int naxz);

        void run(double delta);

		void addPhysicsObject(PhysicsObject physicsObject);
		PhysicsObject subPhysicsObject(PhysicsObject physicsObject);
		PhysicsObject subPhysicsObject(int index);

		int getMinx() const;
		void setMinx(const int value);
		int getMiny() const;
		void setMiny(const int value);
		int getMinz() const;
		void setMinz(const int value);
		int getMaxx() const;
		void setMaxx(const int value);
		int getMaxy() const;
		void setMaxy(const int value);
		int getMaxz() const;
		void setMaxz(const int value);

	private:
		int minx;
		int miny;
		int minz;

		int maxx;
		int maxy;
		int maxz;

		double g = 9.81;

		std::vector<PhysicsObject> pobjects;
};
