#include "collision.h"

Collision::Collision(){
}
    bool Collision::SphereVersusSphere(int x1 ,int y1 ,int z1 ,int size1 ,int x2 ,int y2 ,int z2 ,int size2){

        return     ((x1 - x2) * (x1 - x2) +
                    (y1 - y2) * (y1 - y2) +
                    (z1 - z2) * (z1 - z2)) >= ((size1+size2) * (size1+size2));
    }

    bool Collision::SphereVersusPoint(int sphereX ,int sphereY ,int sphereZ ,int sphereSize ,int PointX ,int PointY ,int PointZ){



        return ((sphereX - PointX) * (sphereX - PointX) +
            (sphereY - PointY) * (sphereY - PointY) +
            (sphereZ - PointZ) * (sphereZ - PointZ) >= (sphereSize * sphereSize));
    }

    bool Collision::BoxVersusPoint(int PointX ,int PointY ,int PointZ ,int boxMinX ,int boxMinY ,int boxMinZ ,int boxMaxX ,int boxMaxY ,int boxMaxZ){



        return (PointX >= boxMinX && PointX <= boxMaxX) &&
               (PointY >= boxMinY && PointY <= boxMaxY) &&
               (PointZ >= boxMinZ && PointZ <= boxMaxZ);
    }

    bool Collision::BoxVersusBox(int boxMinX1 ,int boxMinY1 ,int boxMinZ1 ,int boxMaxX1 ,int boxMaxY1 ,int boxMaxZ1 ,int boxMinX2 ,int boxMinY2 ,int boxMinZ2 ,int boxMaxX2 ,int boxMaxY2 ,int boxMaxZ2){

        return (boxMinX1 <= boxMaxX2 && boxMaxX1 >= boxMinX2) &&
               (boxMinY1 <= boxMaxY2 && boxMaxY1 >= boxMinY2) &&
               (boxMinZ1 <= boxMaxZ2 && boxMaxZ1 >= boxMinZ2);

    }

    bool Collision::SphereVersusBox(int sphereX ,int sphereY ,int sphereZ ,int sphereSize ,int boxMinX ,int boxMinY ,int boxMinZ ,int boxMaxX ,int boxMaxY ,int boxMaxZ){
        //Math.max(box.minX, Math.min(sphere.x, box.maxX);
        int x = Max(boxMinX, Min(sphereX ,boxMaxX));
        int y = Max(boxMinY, Min(sphereY ,boxMaxY));
        int z = Max(boxMinZ, Min(sphereZ ,boxMaxZ));

        return (x - sphereX) * (x - sphereX) +
            (y - sphereY) * (y - sphereY) +
            (z - sphereZ) * (z - sphereZ) < (sphereSize * sphereSize);
    }

    int Collision::Min(int i1 ,int i2){
        if(i1 < i2){
            return i1;
        }else{
            return i2;
        }
    }

    int Collision::Max(int i1 ,int i2){
        if(i1 > i2){
            return i1;
        }else{
            return i2;
        }
    }

