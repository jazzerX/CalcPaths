#pragma once

#include "Point.h"

class IDrawer
{
public:
	virtual void DrawLine(Point sp, Point fp) const = 0;
	virtual void DrawArc(Point sp, Point mp, Point fp) const = 0;
};