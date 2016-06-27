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
		qDebug() << "RUNNING PHYSICS-SIMULATION";
		runSimulation(1.0/60.0);
		if(stop){
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

void PhysicsThread::runSimulation(const double& delta){

	// Collision Border
	for(int i = 0 ; i < pobjectsSphere.size() ; i++) {

		PhysicsSphere* op = pobjectsSphere.at(i);
		if(op->getIsMovable()){
			// is Sphere TODO
			if(true){
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

				if(op->getY()-(op->getSize()) < miny){
					if(op->getVelocityY() < 0){
						op->setVelocityY(-op->getVelocityY() * op->getRemainingEnergy());
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
					op->setVelocityY(op->getVelocityY() + g*delta*op->getMass());
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
	}

	// Collision Sphere on Sphere
	for(int i = 0 ; i < pobjectsSphere.size() ; i++) {
		PhysicsSphere* op1 = pobjectsSphere.at(i);
		for(int j = i ; j < pobjectsSphere.size() ; j++) {
			PhysicsSphere* op2 = pobjectsSphere.at(j);

			// bool Collision::SphereVersusSphere(const int& x1 , const int& y1 , const int& z1 , const int& size1 , const int& x2 , const int& y2 , const int& z2 , const int& size2)
			// Sphere on Sphere
			// SIZE
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

				// double optimizedP = (2.0D * (a1 - a2)) / (e1.getWhight() + e2.getWhight());

				double optimizedP = (2.0 * (a1 - a2)) / (op1->getMass() + op2->getMass());

				// fix
				optimizedP = std::abs(optimizedP);

				qDebug() << optimizedP;

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

				// TODO
				qDebug() << op1->getPosition() << "BEFORE";
				op1->setX(op1->getX() + op1->getVelocityX() * delta);
				op1->setY(op1->getY() + op1->getVelocityY() * delta);
				op1->setZ(op1->getZ() + op1->getVelocityZ() * delta);

				op2->setX(op2->getX() + op2->getVelocityX() * delta);
				op2->setY(op2->getY() + op2->getVelocityY() * delta);
				op2->setZ(op2->getZ() + op2->getVelocityZ() * delta);
				qDebug() << op1->getPosition() << "AFTER";
			}
		}
	}

//	// Collision Shere on Box
//	// bool Collision::SphereVersusBox
//	//(const int& sphereX ,const int& sphereY ,const int& sphereZ ,const int& sphereSize
//	// ,const int& boxMinX ,const int& boxMinY ,const int& boxMinZ ,const int& boxMaxX ,const int& boxMaxY ,const int& boxMaxZ)


//	for(int i = 0 ; i < pobjectsSphere.size() ; i++) {
//		PhysicsSphere* op1 = pobjectsSphere.at(i);
//		for(int j = 0 ; j < pobjectsBox.size() ; j++) {
//			PhysicsBox* op2 = pobjectsBox.at(j);

//			if(Collision::SphereVersusBox( op1->getX() ,op1->getY() ,op1->getZ() ,op1->getSize() ,op2->getMinX() ,op2->getMinY() ,op2->getMinZ() ,op2->getMaxX() ,op2->getMaxY() ,op2->getMaxZ())){
//				double closeDistance = std::abs( op1->getX()-op2->getMaxX());

//				if(closeDistance > std::abs( op1->getX() - op2->getMinX())){
//					closeDistance = std::abs( op1->getX() - op2->getMinX());
//				}

//				if(closeDistance > std::abs( op1->getY() - op2->getMaxY())){
//					closeDistance = std::abs( op1->getY() - op2->getMaxY());
//				}

//				if(closeDistance > std::abs( op1->getY() - op2->getMinY())){
//					closeDistance = std::abs( op1->getY() - op2->getMinY());
//				}

//				if(closeDistance > std::abs( op1->getZ() - op2->getMaxZ())){
//					closeDistance = std::abs( op1->getZ() - op2->getMaxZ());
//				}

//				if(closeDistance > std::abs( op1->getZ() - op2->getMinZ())){
//					closeDistance = std::abs( op1->getZ() - op2->getMinZ());
//				}

//				if(closeDistance == std::abs( op1->getX()-op2->getMaxX())){
//					// maxX
//					if(op1->getVelocityX() < 0){
//						op1->setVelocityX(-op1->getVelocityX());
//					}
//				}else if(closeDistance == std::abs( op1->getX() - op2->getMinX())){
//					// minX
//					if(op1->getVelocityX() > 0){
//						op1->setVelocityX(-op1->getVelocityX());
//					}
//				}else if(closeDistance == std::abs( op1->getY() - op2->getMaxY())){
//					// maxY
//					if(op1->getVelocityY() < 0){
//						op1->setVelocityY(-op1->getVelocityY());
//					}
//				}else if(closeDistance == std::abs( op1->getY() - op2->getMinY())){
//					// minY
//					if(op1->getVelocityY() > 0){
//						op1->setVelocityY(-op1->getVelocityY());
//					}
//				}else if(closeDistance == std::abs( op1->getZ() - op2->getMaxZ())){
//					// maxZ
//					if(op1->getVelocityZ() < 0){
//						op1->setVelocityZ(-op1->getVelocityZ());
//					}
//				}else if(closeDistance == std::abs( op1->getZ() - op2->getMinZ())){
//					// minZ
//					if(op1->getVelocityZ() > 0){
//						op1->setVelocityZ(-op1->getVelocityZ());
//					}
//				}
//			}
//		}
//	}

	// Move
	for(int i = 0 ; i < pobjectsSphere.size() ; i++) {
		PhysicsSphere* op = pobjectsSphere.at(i);
		op->setX(op->getX() + op->getVelocityX()*delta);
		op->setY(op->getY() + op->getVelocityY()*delta);
		op->setZ(op->getZ() + op->getVelocityZ()*delta);
		//qDebug() << op->getVelocity();

	}
	this->msleep(pauseTickTime);
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

