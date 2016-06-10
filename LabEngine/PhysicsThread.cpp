#include "PhysicsThread.h"
#include <vector>

int minx = 0;
int miny = 0;
int minz = 0;

int maxx = 0;
int maxy = 0;
int maxz = 0;

double g = 9.81;

std::vector<PhysicsObject> pobjects;

PhysicsThread::PhysicsThread(int minx ,int miny ,int minz ,int maxx ,int maxy ,int naxz)
{

    this->minx = minx;
    this->miny = miny;
    this->minz = minz;

    this->maxx = maxx;
    this->maxy = maxy;
    this->maxz = maxz;

}


