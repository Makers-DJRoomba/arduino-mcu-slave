#ifndef CONSTANTS_H
#define CONSTANTS_H

#define _USE_MATH_DEFINES

#include <cmath>

const int SlitsPerRevolution = 20;
const float WheelDiameterM   = 0.0693f;   // meters
const float WheelDistanceM   = 0.12035f;  // meters
const float DistancePerSlit = (M_PI * WheelDiameterM)/SlitsPerRev;

#endif