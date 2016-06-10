
#include <vector>
#include "PhysicsObject.h"


class PhysicsThread
{
public:

    int minx;
    int miny;
    int minz;

    int maxx;
    int maxy;
    int maxz;

    double g = 9.81;

    std::vector<PhysicsObject> pobjects;

    PhysicsThread(int minx ,int miny ,int minz ,int maxx ,int maxy ,int naxz);

    void addPhysicsObject(PhysicsObject physicsObject);
    PhysicsObject subPhysicsObject(PhysicsObject physicsObject);
    PhysicsObject subPhysicsObject(int index);

    int getMinx() const;
    void setMinx(int value);
    int getMiny() const;
    void setMiny(int value);
    int getMinz() const;
    void setMinz(int value);
    int getMaxx() const;
    void setMaxx(int value);
    int getMaxy() const;
    void setMaxy(int value);
    int getMaxz() const;
    void setMaxz(int value);
};

int PhysicsThread::getMiny() const
{
    return miny;
}

void PhysicsThread::setMiny(int value)
{
    miny = value;
}

int PhysicsThread::getMinz() const
{
return minz;
}

void PhysicsThread::setMinz(int value)
{
minz = value;
}

int PhysicsThread::getMaxx() const
{
return maxx;
}

void PhysicsThread::setMaxx(int value)
{
maxx = value;
}

int PhysicsThread::getMaxy() const
{
return maxy;
}

void PhysicsThread::setMaxy(int value)
{
maxy = value;
}

int PhysicsThread::getMaxz() const
{
return maxz;
}

void PhysicsThread::setMaxz(int value)
{
maxz = value;
}

int PhysicsThread::getMinx() const
{
    return minx;
}

void PhysicsThread::setMinx(int value)
{
    minx = value;
}
