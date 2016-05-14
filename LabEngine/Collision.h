#pragma once

class Collision
{
	public:
		Collision();
        static bool SphereVersusSphere(const int& x1 ,const int& y1 ,const int& z1 ,const int& size1 ,const int& x2 ,const int& y2 ,const int& z2 ,const int& size2);
        static bool SphereVersusPoint(const int& sphereX ,const int& sphereY ,const int& sphereZ ,const int& sphereSize ,const int& PointX ,const int& PointY ,const int& PointZ);
        static bool BoxVersusPoint(const int& PointX ,const int& PointY ,const int& PointZ ,const int& boxMinX ,const int& boxMinY ,const int& boxMinZ ,const int& boxMaxX ,const int& boxMaxY ,const int& boxMaxZ);
        static bool BoxVersusBox(const int& boxMinX1 ,const int& boxMinY1 ,const int& boxMinZ1 ,const int& boxMaxX1 ,const int& boxMaxY1 ,const int& boxMaxZ1 ,const int& boxMinX2 ,const int& boxMinY2 ,const int& boxMinZ2 ,const int& boxMaxX2 ,const int& boxMaxY2 ,const int& boxMaxZ2);
        static bool SphereVersusBox(const int& sphereX ,const int& sphereY ,const int& sphereZ ,const int& sphereSize ,const int& boxMinX ,const int& boxMinY ,const int& boxMinZ ,const int& boxMaxX ,const int& boxMaxY ,const int& boxMaxZ);
        static int Min(const int& i1 , const int& i2);
        static int Max(const int& i1 ,const int& i2);

};
