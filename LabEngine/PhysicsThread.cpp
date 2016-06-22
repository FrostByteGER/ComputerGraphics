#include "PhysicsThread.h"
#include "Collision.h"
#include <cmath>
#include <vector>
#include <algorithm>
#include <iterator>


std::vector<PhysicsObject> pobjects;

int minx;
int miny;
int minz;

int maxx;
int maxy;
int maxz;

double g = 9.81;

PhysicsThread::PhysicsThread(int minx ,int miny ,int minz ,int maxx ,int maxy ,int naxz)
{

    this->minx = minx;
    this->miny = miny;
    this->minz = minz;

    this->maxx = maxx;
    this->maxy = maxy;
    this->maxz = naxz;

}

void run(double delta){

    // Collision Border
    for(int i = 0 ; i < pobjects.size() ; i++) {
        PhysicsObject op = pobjects.at(i);

        if(op.getIsMovable()){
            if(op.getX() < minx ){
                if(op.getVelocityX() < 0){
                    op.setVelocityX(-op.getVelocityX());
                }else{
                    op.setVelocityX(op.getVelocityX()*1.01);
                }
            }else if(op.getX() > maxx) {
                if(op.getVelocityX() > 0){
                    op.setVelocityX(-op.getVelocityX());
                }else{
                    op.setVelocityX(op.getVelocityX()*1.01);
                }
            }

            if(op.getY() < miny){
                if(op.getVelocityY() < 0){
                    op.setVelocityY(-op.getVelocityY());
                }else{
                    op.setVelocityY(op.getVelocityY()*1.01);
                }
            }else{
                if(op.getY() > maxy){
                    if(op.getVelocityY() > 0){
                        op.setVelocityY(-op.getVelocityY());
                    }else{
                        op.setVelocityY(op.getVelocityY()*1.01);
                    }
                }

                // G
                op.setVelocityY(g*delta*op.getMass());

            }

            if(op.getZ() < minz){
                if(op.getVelocityZ() < 0){
                    op.setVelocityZ(-op.getVelocityZ());
                }else{
                    op.setVelocityZ(op.getVelocityZ()*1.01);
                }
            }else if(op.getZ() > maxz){
                if(op.getVelocityZ() > 0){
                    op.setVelocityZ(-op.getVelocityZ());
                }else{
                    op.setVelocityZ(op.getVelocityZ()*1.01);
                }
            }
        }
    }

    // Collision
    for(int i = 0 ; i < pobjects.size() ; i++) {
        PhysicsObject op1 = pobjects.at(i);
        for(int j = i ; j < pobjects.size() ; j++) {
            PhysicsObject op2 = pobjects.at(j);

            // bool Collision::SphereVersusSphere(const int& x1 , const int& y1 , const int& z1 , const int& size1 , const int& x2 , const int& y2 , const int& z2 , const int& size2)

            if(op1.getType() == 2 && op2.getType() == 2){

                // SIZE
                if(Collision::SphereVersusSphere(op1.getX() ,op1.getY() ,op1.getZ() ,((PhysicsShere*)&op1)->getSize() ,op2.getX() ,op2.getY() ,op2.getZ() ,((PhysicsShere*)&op2)->getSize())){

                    double tempX (op1.getX() - op2.getX());
                    double tempY (op1.getY() - op2.getY());
                    double tempZ (op1.getZ() - op2.getZ());

                    double norm = sqrt(tempX*tempX + tempY*tempY + tempZ*tempZ);

                    tempX = tempX / norm;
                    tempY = tempY / norm;
                    tempZ = tempZ / norm;

                    double a1 = (op1.getVelocityX() * tempX) + (op1.getVelocityY() * tempY) + (op1.getVelocityZ() * tempZ);
                    double a2 = (op2.getVelocityX() * tempX) + (op2.getVelocityY() * tempY) + (op2.getVelocityZ() * tempZ);

                    // double optimizedP = (2.0D * (a1 - a2)) / (e1.getWhight() + e2.getWhight());

                    double optimizedP = (2.0 * (a1 - a2)) / (op1.getMass() + op2.getMass());

                    // fix
                    optimizedP = abs(optimizedP);

                    // 0.9 Verlusst
                    if(op1.getIsMovable()){
                        op1.setVelocityX( op1.getVelocityX() + (optimizedP * op2.getMass() * tempX) * 0.9);
                        op1.setVelocityY( op1.getVelocityY() + (optimizedP * op2.getMass() * tempY) * 0.9);
                        op1.setVelocityZ( op1.getVelocityZ() + (optimizedP * op2.getMass() * tempZ) * 0.9);
                    }

                    if(op2.getIsMovable()){
                        op2.setVelocityX( op2.getVelocityX() + (optimizedP * op1.getMass() * tempX) * 0.9);
                        op2.setVelocityY( op2.getVelocityY() + (optimizedP * op1.getMass() * tempY) * 0.9);
                        op2.setVelocityZ( op2.getVelocityZ() + (optimizedP * op1.getMass() * tempZ) * 0.9);
                    }

                    // TODO
                }
            }
            if(op1.getType() == 2 && op2.getType() == 1){

            }
        }

    }

    // Move
    for(int i = 0 ; i < pobjects.size() ; i++) {
        PhysicsObject op = pobjects.at(i);

        op.setX(op.getVelocityX()*delta);
        op.setY(op.getVelocityY()*delta);
        op.setZ(op.getVelocityZ()*delta);
    }
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

void addPhysicsObject(PhysicsObject physicsObject)
{
    pobjects.push_back(physicsObject);
}


