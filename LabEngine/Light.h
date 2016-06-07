#pragma once

#include "Transform3D.h"
#include <QColor>

struct Light{
	Transform3D transform;
	QColor lightColor;
};
