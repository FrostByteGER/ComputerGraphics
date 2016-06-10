#include "Collision.h"
#include <cmath>

Collision::Collision()
{

}

bool Collision::SphereVersusSphere(const int& x1 , const int& y1 , const int& z1 , const int& size1 , const int& x2 , const int& y2 , const int& z2 , const int& size2)
{

    return     (std::abs((x1 - x2) * (x1 - x2)) +
                std::abs((y1 - y2) * (y1 - y2)) +
                std::abs((z1 - z2) * (z1 - z2))) <=
                std::abs((size1+size2) * (size1+size2));
}

bool Collision::SphereVersusPoint(const int& sphereX , const int& sphereY , const int& sphereZ , const int& sphereSize , const int& PointX , const int& PointY , const int& PointZ)
{
	return ((sphereX - PointX) * (sphereX - PointX) +
			(sphereY - PointY) * (sphereY - PointY) +
			(sphereZ - PointZ) * (sphereZ - PointZ) >= (sphereSize * sphereSize));
}

bool Collision::BoxVersusPoint(const int& PointX ,const int& PointY ,const int& PointZ ,const int& boxMinX ,const int& boxMinY ,const int& boxMinZ ,const int& boxMaxX ,const int& boxMaxY ,const int& boxMaxZ)
{
	return (PointX >= boxMinX && PointX <= boxMaxX) &&
			(PointY >= boxMinY && PointY <= boxMaxY) &&
			(PointZ >= boxMinZ && PointZ <= boxMaxZ);
}

bool Collision::BoxVersusBox(const int& boxMinX1 ,const int& boxMinY1 ,const int& boxMinZ1 ,const int& boxMaxX1 ,const int& boxMaxY1 ,const int& boxMaxZ1 ,const int& boxMinX2 ,const int& boxMinY2 ,const int& boxMinZ2 ,const int& boxMaxX2 ,const int& boxMaxY2 ,const int& boxMaxZ2)
{
	return (boxMinX1 <= boxMaxX2 && boxMaxX1 >= boxMinX2) &&
			(boxMinY1 <= boxMaxY2 && boxMaxY1 >= boxMinY2) &&
			(boxMinZ1 <= boxMaxZ2 && boxMaxZ1 >= boxMinZ2);

}

bool Collision::SphereVersusBox(const int& sphereX ,const int& sphereY ,const int& sphereZ ,const int& sphereSize ,const int& boxMinX ,const int& boxMinY ,const int& boxMinZ ,const int& boxMaxX ,const int& boxMaxY ,const int& boxMaxZ)
{
	//Math.max(box.minX, Math.min(sphere.x, box.maxX);
	int x = Max(boxMinX, Min(sphereX ,boxMaxX));
	int y = Max(boxMinY, Min(sphereY ,boxMaxY));
	int z = Max(boxMinZ, Min(sphereZ ,boxMaxZ));

	return (x - sphereX) * (x - sphereX) +
			(y - sphereY) * (y - sphereY) +
			(z - sphereZ) * (z - sphereZ) < (sphereSize * sphereSize);
}


int Collision::Min(const int& i1 ,const int& i2)
{
	if(i1 < i2){
		return i1;
	}else{
		return i2;
	}
}

int Collision::Max(const int& i1 ,const int& i2)
{
	if(i1 > i2){
		return i1;
	}else{
		return i2;
	}
}

