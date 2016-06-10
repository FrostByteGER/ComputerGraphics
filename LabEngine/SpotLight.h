#pragma once

#include "Light.h"

struct SpotLight : public Light {
	float coneRadius;
	float coneLength;
};
