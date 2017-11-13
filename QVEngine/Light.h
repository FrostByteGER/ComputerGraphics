#pragma once

#include "VTransform.h"
#include <QColor>

struct Light{
	VTransform transform;
	QColor lightColor;
	float lightIntensity = 1.0f;
};
