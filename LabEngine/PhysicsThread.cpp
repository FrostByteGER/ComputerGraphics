#include "PhysicsThread.h"
#include "PhysicsObject.h"
#include "Collision.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>
#include <QDebug>





PhysicsThread::PhysicsThread()
{
}

PhysicsThread::PhysicsThread(int minx ,int miny ,int minz ,int maxx ,int maxy ,int maxz)
{

	this->minx = minx;
	this->miny = miny;
	this->minz = minz;

	this->maxx = maxx;
	this->maxy = maxy;
	this->maxz = maxz;

}

PhysicsThread::~PhysicsThread()
{

}

void PhysicsThread::run(){
	qDebug() << "SUCCESSFULLY STARTED UP PHYSICS-SIMULATION";
	forever{
		mutex.lock();
		//qDebug() << "RUNNING PHYSICS-SIMULATION";
		runSimulation();
		if(stop){
			mutex.unlock();
			break;
		}
		if(bPause){
			pauseManager.wait(&mutex);
		}
		mutex.unlock();
	}
}

void PhysicsThread::TogglePause()
{
	bPause = !bPause;
	if(!bPause){
		pauseManager.wakeAll();
	}
}

void PhysicsThread::pause()
{
	bPause = true;
}

void PhysicsThread::resume()
{
	bPause = false;
	pauseManager.wakeAll();
}

void PhysicsThread::quit()
{
	stop = true;
	QThread::quit();
	qDebug() << "STOPPING PHYSICS-THREAD";
}

void PhysicsThread::runSimulation(){
	auto startTime = std::chrono::high_resolution_clock::now();

	// Collision Border
	for(size_t i = 0 ; i < pobjectsSphere.size() ; i++) {

		PhysicsSphere* op = pobjectsSphere.at(i);
		if(op->getIsMovable()){
			if(op->getX()-(op->getSize()) < minx ){
				if(op->getVelocityX() < 0){
					op->setVelocityX(-op->getVelocityX());
				}else{
					op->setVelocityX(op->getVelocityX());
				}
			}else if(op->getX()+(op->getSize()) > maxx) {
				if(op->getVelocityX() > 0){
					op->setVelocityX(-op->getVelocityX());
				}else{
					op->setVelocityX(op->getVelocityX());
				}
			}

            if(op->getY()-(op->getSize()) <= miny){

                op->setVelocityY(op->getVelocityY() * op->getVerticalFriction());

                if(std::abs(op->getVelocityY()) <= -g){
                    op->setVelocityY(0.0);
                    op->setY(miny+op->getSize());
                }else{
                    //qDebug() << "v" << op->getVelocityY() << " " << g;
                }

                //qDebug() << "v" << op->getVelocityY() << " " << g << "|" << deltaTimeMS;

                if(deltaTimeMS < 1 || true){
                    op->setVelocityX(op->getVelocityX() * (1 - (op->getHorizontalFriction())));
                    op->setVelocityZ(op->getVelocityZ() * (1 - (op->getHorizontalFriction())));
                    //qDebug() << "v" << op->getVelocityY() << " " << g << " " << deltaTimeMS;

                }

				if(op->getVelocityY() < 0){
                    //op->setVelocityY(-op->getVelocityY() * op->getRemainingEnergy());
                    op->setVelocityY(-op->getVelocityY());

                }else{
					op->setVelocityY(op->getVelocityY());
				}
			}else{
				if(op->getY()+(op->getSize()) > maxy){
					if(op->getVelocityY() > 0){
						op->setVelocityY(-op->getVelocityY());
					}else{
						op->setVelocityY(op->getVelocityY());
					}
				}

				// Gravity
                op->setVelocityY(op->getVelocityY() + g*deltaTimeMS*op->getMass());

			}

			if(op->getZ()-(op->getSize()) < minz){
				if(op->getVelocityZ() < 0){
					op->setVelocityZ(-op->getVelocityZ());
				}else{
					op->setVelocityZ(op->getVelocityZ());
				}
			}else if(op->getZ()+(op->getSize()) > maxz){
				if(op->getVelocityZ() > 0){
					op->setVelocityZ(-op->getVelocityZ());
				}else{
					op->setVelocityZ(op->getVelocityZ());
				}
			}
		}
	}

	// Collision Sphere on Sphere
	for(size_t i = 0 ; i < pobjectsSphere.size() ; i++) {
		PhysicsSphere* op1 = pobjectsSphere.at(i);
		for(size_t j = i ; j < pobjectsSphere.size() ; j++) {
			PhysicsSphere* op2 = pobjectsSphere.at(j);

			// Sphere on Sphere
			if(i != j && Collision::SphereVersusSphere(op1->getX() ,op1->getY() ,op1->getZ() ,op1->getSize() ,op2->getX() ,op2->getY() ,op2->getZ() ,op2->getSize())){

				double tempX (op1->getX() - op2->getX());
				double tempY (op1->getY() - op2->getY());
				double tempZ (op1->getZ() - op2->getZ());

				double norm = sqrt(tempX*tempX + tempY*tempY + tempZ*tempZ);

				tempX = tempX / norm;
				tempY = tempY / norm;
				tempZ = tempZ / norm;

				double a1 = (op1->getVelocityX() * tempX) + (op1->getVelocityY() * tempY) + (op1->getVelocityZ() * tempZ);
				double a2 = (op2->getVelocityX() * tempX) + (op2->getVelocityY() * tempY) + (op2->getVelocityZ() * tempZ);

				double optimizedP = (2.0 * (a1 - a2)) / (op1->getMass() + op2->getMass());

				// fix
				optimizedP = std::abs(optimizedP);

				// 0.9 Verlusst
				if(op1->getIsMovable()){
					op1->setVelocityX( op1->getVelocityX() + (optimizedP * op2->getMass() * tempX) * (op1->getRemainingEnergy()*op2->getRemainingEnergy()));
					op1->setVelocityY( op1->getVelocityY() + (optimizedP * op2->getMass() * tempY) * (op1->getRemainingEnergy()*op2->getRemainingEnergy()));
					op1->setVelocityZ( op1->getVelocityZ() + (optimizedP * op2->getMass() * tempZ) * (op1->getRemainingEnergy()*op2->getRemainingEnergy()));
				}

				if(op2->getIsMovable()){
					op2->setVelocityX( op2->getVelocityX() - (optimizedP * op1->getMass() * tempX) * (op1->getRemainingEnergy()*op2->getRemainingEnergy()));
					op2->setVelocityY( op2->getVelocityY() - (optimizedP * op1->getMass() * tempY) * (op1->getRemainingEnergy()*op2->getRemainingEnergy()));
					op2->setVelocityZ( op2->getVelocityZ() - (optimizedP * op1->getMass() * tempZ) * (op1->getRemainingEnergy()*op2->getRemainingEnergy()));
				}

				if(!op1->getIsMovable() && op2->getIsMovable()){
					op2->setX(op2->getX() - op1->getVelocityX() * deltaTimeMS);
					op2->setY(op2->getY() - op1->getVelocityY() * deltaTimeMS);
					op2->setZ(op2->getZ() - op1->getVelocityZ() * deltaTimeMS);

					op1->setVelocityX(0.0);
					op1->setVelocityY(0.0);
					op1->setVelocityZ(0.0);

				}else if(op1->getIsMovable() && !op2->getIsMovable()){
					op1->setX(op1->getX() - op2->getVelocityX() * deltaTimeMS);
					op1->setY(op1->getY() - op2->getVelocityY() * deltaTimeMS);
					op1->setZ(op1->getZ() - op2->getVelocityZ() * deltaTimeMS);

					op2->setVelocityX(0.0);
					op2->setVelocityY(0.0);
					op2->setVelocityZ(0.0);
				}


				op1->setX(op1->getX() + op1->getVelocityX() * deltaTimeMS);
				op1->setY(op1->getY() + op1->getVelocityY() * deltaTimeMS);
				op1->setZ(op1->getZ() + op1->getVelocityZ() * deltaTimeMS);

				op2->setX(op2->getX() + op2->getVelocityX() * deltaTimeMS);
				op2->setY(op2->getY() + op2->getVelocityY() * deltaTimeMS);
				op2->setZ(op2->getZ() + op2->getVelocityZ() * deltaTimeMS);
			}
		}
	}

	for(size_t i = 0 ; i < pobjectsSphere.size() ; i++) {
		PhysicsSphere* op1 = pobjectsSphere.at(i);
		for(size_t j = 0 ; j < pobjectsBox.size() ; j++) {
			PhysicsBox* op2 = pobjectsBox.at(j);



			if(Collision::SphereVersusBox( op1->getX() ,op1->getY() ,op1->getZ() ,op1->getSize() ,op2->getMinX()+op2->getX() ,op2->getMinY()+op2->getY() ,op2->getMinZ()+op2->getZ() ,op2->getMaxX()+op2->getX() ,op2->getMaxY()+op2->getY() ,op2->getMaxZ()+op2->getZ())){
				if(op1->getID() == 1 && op2->getID() == 2){
					qDebug() << "WIN!!!!";
				}
                if((op1->getX()+op1->getSize()) > op2->getMinX()+op2->getX() && op1->getX() < op2->getMinX()+op2->getX()){
                    if(op1->getVelocityX() > 0){
						op1->setVelocityX(-op1->getVelocityX());
					}
				}
                if((op1->getX()-op1->getSize()) < op2->getMaxX()+op2->getX() && op1->getX() > op2->getMaxX()+op2->getX()){
                    if(op1->getVelocityX() < 0){
						op1->setVelocityX(-op1->getVelocityX());
					}
				}

                if((op1->getY()+op1->getSize()) > op2->getMinY()+op2->getY() && op1->getY() < op2->getMinY()+op2->getY()){
					if(op1->getVelocityY() > 0){
						op1->setVelocityY(-op1->getVelocityY());
					}
				}
                if((op1->getY()-op1->getSize()) < op2->getMaxY()+op2->getY() && op1->getY() > op2->getMaxY()+op2->getY()){

					if(op1->getVelocityY() < 0){
						op1->setVelocityY(-op1->getVelocityY());
					}
				}

                if((op1->getZ()+op1->getSize()) > op2->getMinZ()+op2->getZ() && op1->getZ() < op2->getMinZ()+op2->getZ()){
					if(op1->getVelocityZ() > 0){
						op1->setVelocityZ(-op1->getVelocityZ());
					}
				}
                if((op1->getZ()-op1->getSize()) < op2->getMaxZ()+op2->getZ() && op1->getZ() > op2->getMaxZ()+op2->getZ()){
					if(op1->getVelocityZ() < 0){
						op1->setVelocityZ(-op1->getVelocityZ());
					}
				}
			}
		}
	}

	// Move
	for(size_t i = 0 ; i < pobjectsSphere.size() ; i++) {
		PhysicsSphere* op = pobjectsSphere.at(i);
		if(op->getIsMovable()){
			op->setX(op->getX() + op->getVelocityX()*deltaTimeMS);
			op->setY(op->getY() + op->getVelocityY()*deltaTimeMS);
			op->setZ(op->getZ() + op->getVelocityZ()*deltaTimeMS);
			//TODO: REMOVE
//			if(op->velocityToAdd.x() > 0.0f || op->velocityToAdd.y() > 0.0f, op->velocityToAdd.z() > 0.0f){
//				op->setX(op->getX() + op->velocityToAdd.x()*deltaTimeMS);
//				op->setY(op->getY() + op->velocityToAdd.y()*deltaTimeMS);
//				op->setZ(op->getZ() + op->velocityToAdd.z()*deltaTimeMS);
//				op->velocityToAdd -= QVector3D(deltaTimeMS,deltaTimeMS,deltaTimeMS);
//			}
		}else{
			op->setVelocityX(0.0);
			op->setVelocityY(0.0);
			op->setVelocityZ(0.0);
		}
	}
	if(pauseTickTime > 0.0){
		this->msleep(pauseTickTime);
	}
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time = endTime - startTime;
	deltaTimeNS = std::chrono::duration_cast<std::chrono::nanoseconds>(time).count();
    deltaTimeMS = deltaTimeNS / 1000000.0;
#ifdef __MINGW32__
	//MinGW specific fix, allows partially smooth physics simulation
	if(deltaTimeMS == 0){
        deltaTimeMS = 0.000005;
	}
#endif
	//qDebug() << "DeltaT NS: " << deltaTimeNS << " DeltaT MS: " << deltaTimeMS;
}

int PhysicsThread::getMiny() const
{
	return miny;
}

void PhysicsThread::setMiny(const int value)
{
	miny = value;
}

int PhysicsThread::getMinz() const
{
	return minz;
}

void PhysicsThread::setMinz(const int value)
{
	minz = value;
}

int PhysicsThread::getMaxx() const
{
	return maxx;
}

void PhysicsThread::setMaxx(const int value)
{
	maxx = value;
}

int PhysicsThread::getMaxy() const
{
	return maxy;
}

void PhysicsThread::setMaxy(const int value)
{
	maxy = value;
}

int PhysicsThread::getMaxz() const
{
	return maxz;
}

void PhysicsThread::setMaxz(const int value)
{
	maxz = value;
}

int PhysicsThread::getMinx() const
{
	return minx;
}

void PhysicsThread::setMinx(const int value)
{
	minx = value;
}

void PhysicsThread::registerPhysicsSphere(PhysicsSphere* physicsObject)
{
	pobjectsSphere.push_back(physicsObject);
}

void PhysicsThread::deregisterPhysicsSphere(PhysicsSphere* physicsObject)
{
	pobjectsSphere.erase(std::remove(pobjectsSphere.begin(), pobjectsSphere.end(),physicsObject), pobjectsSphere.end());
}

void PhysicsThread::registerPhysicsBox(PhysicsBox* physicsObject)
{
	pobjectsBox.push_back(physicsObject);
}

void PhysicsThread::deregisterPhysicsBox(PhysicsBox* physicsObject)
{
	pobjectsBox.erase(std::remove(pobjectsBox.begin(), pobjectsBox.end(),physicsObject), pobjectsBox.end());
}
