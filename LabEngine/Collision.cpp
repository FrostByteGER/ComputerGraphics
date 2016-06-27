#include "Collision.h"
#include <cmath>

Collision::Collision()
{

}

bool Collision::SphereVersusSphere(const double& x1 , const double& y1 , const double& z1 , const double& size1 , const double& x2 , const double& y2 , const double& z2 , const double& size2)
{

    return     (std::abs((x1 - x2) * (x1 - x2)) +
                std::abs((y1 - y2) * (y1 - y2)) +
                std::abs((z1 - z2) * (z1 - z2))) <=
                std::abs((size1+size2) * (size1+size2));
}

bool Collision::SphereVersusPoint(const double& sphereX , const double& sphereY , const double& sphereZ , const double& sphereSize , const double& PointX , const double& PointY , const double& PointZ)
{
	return ((sphereX - PointX) * (sphereX - PointX) +
			(sphereY - PointY) * (sphereY - PointY) +
			(sphereZ - PointZ) * (sphereZ - PointZ) >= (sphereSize * sphereSize));
}

bool Collision::BoxVersusPoint(const double& PointX ,const double& PointY ,const double& PointZ ,const double& boxMinX ,const double& boxMinY ,const double& boxMinZ ,const double& boxMaxX ,const double& boxMaxY ,const double& boxMaxZ)
{
	return (PointX >= boxMinX && PointX <= boxMaxX) &&
			(PointY >= boxMinY && PointY <= boxMaxY) &&
			(PointZ >= boxMinZ && PointZ <= boxMaxZ);
}

bool Collision::BoxVersusBox(const double& boxMinX1 ,const double& boxMinY1 ,const double& boxMinZ1 ,const double& boxMaxX1 ,const double& boxMaxY1 ,const double& boxMaxZ1 ,const double& boxMinX2 ,const double& boxMinY2 ,const double& boxMinZ2 ,const double& boxMaxX2 ,const double& boxMaxY2 ,const double& boxMaxZ2)
{
	return (boxMinX1 <= boxMaxX2 && boxMaxX1 >= boxMinX2) &&
			(boxMinY1 <= boxMaxY2 && boxMaxY1 >= boxMinY2) &&
			(boxMinZ1 <= boxMaxZ2 && boxMaxZ1 >= boxMinZ2);

}

bool Collision::SphereVersusBox(const double& sphereX ,const double& sphereY ,const double& sphereZ ,const double& sphereSize ,const double& boxMinX ,const double& boxMinY ,const double& boxMinZ ,const double& boxMaxX ,const double& boxMaxY ,const double& boxMaxZ)
{
	//Math.max(box.minX, Math.min(sphere.x, box.maxX);
	double x = Max(boxMinX, Min(sphereX ,boxMaxX));
	double y = Max(boxMinY, Min(sphereY ,boxMaxY));
	double z = Max(boxMinZ, Min(sphereZ ,boxMaxZ));

	return (x - sphereX) * (x - sphereX) +
			(y - sphereY) * (y - sphereY) +
			(z - sphereZ) * (z - sphereZ) < (sphereSize * sphereSize);
}


double Collision::Min(const double& i1 ,const double& i2)
{
	if(i1 < i2){
		return i1;
	}else{
		return i2;
	}
}

double Collision::Max(const double& i1 ,const double& i2)
{
	if(i1 > i2){
		return i1;
	}else{
		return i2;
	}
}

