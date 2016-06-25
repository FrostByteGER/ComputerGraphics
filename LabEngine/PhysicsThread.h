#pragma once

#include <QThread>
#include <vector>
#include "PhysicsObject.h"
#include <limits>
#include <QMutex>
#include <QWaitCondition>


class PhysicsThread : public QThread
{
	public:

		PhysicsThread();
		PhysicsThread(int minx , int miny , int minz , int maxx , int maxy , int maxz);
		~PhysicsThread();

		void runSimulation(const double& delta);

		void registerPhysicsSphere(PhysicsSphere* physicsObject);
		void deregisterPhysicsSphere(PhysicsSphere* physicsObject);
		PhysicsObject subPhysicsSphere(PhysicsSphere* physicsObject);
		PhysicsObject subPhysicsSphere(int index);

		void registerPhysicsBox(PhysicsBox* physicsObject);
		void deregisterPhysicsBox(PhysicsBox* physicsObject);
		PhysicsObject subPhysicsBox(PhysicsBox* physicsObject);
        PhysicsObject subPhysicsBox(int index);

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

		void TogglePause();
		void pause();
		void resume();

	public slots:
		virtual void quit();

	private:
		int minx = std::numeric_limits<int>::min();
		int miny = std::numeric_limits<int>::min();
		int minz = std::numeric_limits<int>::min();

		int maxx = std::numeric_limits<int>::max();
		int maxy = std::numeric_limits<int>::max();
		int maxz = std::numeric_limits<int>::max();

		double g = 9.81;
		bool stop = false;
		bool bPause = false;

		// Observer, do not delete pointers!
		std::vector<PhysicsObject*> pobjects;
		std::vector<PhysicsSphere*> pobjectsSphere;
		std::vector<PhysicsBox*> pobjectsBox;

		QWaitCondition pauseManager;
		QMutex mutex;

		virtual void run();
};
