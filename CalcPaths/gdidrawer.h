#pragma once
#include "Drawer.h"

class CGDIDrawer : public IDrawer
{
private:
	CDC* m_dc;
public:
	CGDIDrawer(CDC* dc);

	virtual void DrawLine(Point sp, Point fp) const override;
	virtual void DrawArc(Point sp, Point mp, Point fp) const override;
};
