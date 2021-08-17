#pragma once

#include "Point.h"

class IDrawer
{
public:
	virtual void DrawLine(Point sp, Point fp) = 0;
	virtual void DrawArc(Point sp, Point mp, Point fp) = 0;
};