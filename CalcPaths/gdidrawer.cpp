#include "pch.h"
#include "gdidrawer.h"

CGDIDrawer::CGDIDrawer(CDC* dc) : m_dc(dc) { }

void CGDIDrawer::DrawLine(Point sp, Point fp) const
{
	m_dc->MoveTo(sp.m_nx, sp.m_ny);
	m_dc->LineTo(fp.m_nx, fp.m_ny);
}

void CGDIDrawer::DrawArc(Point sp, Point mp, Point fp) const
{
	double dblSpAngle = ::atan2(1. * (mp.m_ny - sp.m_ny), (sp.m_nx - mp.m_nx));
	double dblSweepAngle = ::atan2(1. * (mp.m_ny - fp.m_ny), (fp.m_nx - mp.m_nx));
	double dblRadius = ::sqrt(:: pow(fp.m_nx - mp.m_nx, 2) + ::pow(fp.m_ny - mp.m_ny, 2));

	m_dc->Arc(mp.m_nx - dblRadius, mp.m_ny - dblRadius, mp.m_nx + dblRadius, mp.m_ny + dblRadius, mp.m_nx + dblRadius * ::cos(dblSpAngle),
		mp.m_ny - dblRadius * ::sin(dblSpAngle), mp.m_nx + dblRadius * ::cos(dblSweepAngle), mp.m_ny - dblRadius * ::sin(dblSweepAngle));
}

