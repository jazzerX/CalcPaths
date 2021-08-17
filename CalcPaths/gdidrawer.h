#pragma once
#include "Drawer.h"

class CGDIDrawer : public IDrawer
{
private:
	CDC* m_dc;
public:
	CGDIDrawer(CDC* dc);

	virtual void DrawLine(Point sp, Point fp) override;
	virtual void DrawArc(Point sp, Point mp, Point fp) override;
};
