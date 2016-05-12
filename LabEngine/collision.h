#ifndef COLLISION_H
#define COLLISION_H


class Collision
{
    public:Collision();
    bool SphereVersusSphere(int x1 ,int y1 ,int z1 ,int size1 ,int x2 ,int y2 ,int z2 ,int size2);
    bool SphereVersusPoint(int sphereX ,int sphereY ,int sphereZ ,int sphereSize ,int PointX ,int PointY ,int PointZ);
    bool BoxVersusPoint(int PointX ,int PointY ,int PointZ ,int boxMinX ,int boxMinY ,int boxMinZ ,int boxMaxX ,int boxMaxY ,int boxMaxZ);
    bool BoxVersusBox(int boxMinX1 ,int boxMinY1 ,int boxMinZ1 ,int boxMaxX1 ,int boxMaxY1 ,int boxMaxZ1 ,int boxMinX2 ,int boxMinY2 ,int boxMinZ2 ,int boxMaxX2 ,int boxMaxY2 ,int boxMaxZ2);
    bool SphereVersusBox(int sphereX ,int sphereY ,int sphereZ ,int sphereSize ,int boxMinX ,int boxMinY ,int boxMinZ ,int boxMaxX ,int boxMaxY ,int boxMaxZ);
    int Min(int i1 ,int i2);
    int Max(int i1 ,int i2);

};

#endif // COLLISION_H
