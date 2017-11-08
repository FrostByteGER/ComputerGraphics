#pragma once

#include <QThread>
#include <vector>
#include "PhysicsObject.h"
#include <limits>
#include <QMutex>
#include <QWaitCondition>
#include <chrono>

class PhysicsBox;
class PhysicsSphere;
class PhysicsObject;

class PhysicsThread : public QThread
{
	public:

		PhysicsThread();
		PhysicsThread(int minx , int miny , int minz , int maxx , int maxy , int maxz);
		~PhysicsThread();

		void runSimulation();

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
		int minx = -25;
		int miny = 0;
		int minz = -12.5;

		int maxx = 25;
		int maxy = 25;
		int maxz = 12.5;

		double g = -0.0981;
		bool stop = false;
		bool bPause = false;
		int pauseTickTime = 0;
		double deltaTimeNS = 0.0;
		double deltaTimeMS = 0.0;
		std::chrono::high_resolution_clock timer;

		// Observer, do not delete pointers!
		std::vector<PhysicsObject*> pobjects;
		std::vector<PhysicsSphere*> pobjectsSphere;
		std::vector<PhysicsBox*> pobjectsBox;

		QWaitCondition pauseManager;
		QMutex mutex;

		virtual void run();
};
