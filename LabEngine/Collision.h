#pragma once

class Collision
{
	public:
		Collision();
		static bool SphereVersusSphere(const double& x1 ,const double& y1 ,const double& z1 ,const double& size1 ,const double& x2 ,const double& y2 ,const double& z2 ,const double& size2);
		static bool SphereVersusPoint(const double& sphereX ,const double& sphereY ,const double& sphereZ ,const double& sphereSize ,const double& PointX ,const double& PointY ,const double& PointZ);
		static bool BoxVersusPoint(const double& PointX ,const double& PointY ,const double& PointZ ,const double& boxMinX ,const double& boxMinY ,const double& boxMinZ ,const double& boxMaxX ,const double& boxMaxY ,const double& boxMaxZ);
		static bool BoxVersusBox(const double& boxMinX1 ,const double& boxMinY1 ,const double& boxMinZ1 ,const double& boxMaxX1 ,const double& boxMaxY1 ,const double& boxMaxZ1 ,const double& boxMinX2 ,const double& boxMinY2 ,const double& boxMinZ2 ,const double& boxMaxX2 ,const double& boxMaxY2 ,const double& boxMaxZ2);
		static bool SphereVersusBox(const double& sphereX ,const double& sphereY ,const double& sphereZ ,const double& sphereSize ,const double& boxMinX ,const double& boxMinY ,const double& boxMinZ ,const double& boxMaxX ,const double& boxMaxY ,const double& boxMaxZ);
		static double Min(const double& i1 , const double& i2);
		static double Max(const double& i1 ,const double& i2);

};
