#include "PhysicsThread.h"
#include <vector>

PhysicsThread::PhysicsThread(int minx ,int miny ,int minz ,int maxx ,int maxy ,int naxz)
{

    this->minx = minx;
    this->miny = miny;
    this->minz = minz;

    this->maxx = maxx;
    this->maxy = maxy;
    this->maxz = maxz;

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
