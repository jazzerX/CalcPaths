#include "pch.h"
#include "gdidrawer.h"

CGDIDrawer::CGDIDrawer(CDC* dc)
{
	m_dc = dc;
}

void CGDIDrawer::DrawLine(Point sp, Point fp)
{
	m_dc->MoveTo(sp.m_nx, sp.m_ny);
	m_dc->LineTo(fp.m_nx, fp.m_ny);
}

void CGDIDrawer::DrawArc(Point sp, Point mp, Point fp)
{
	double sp_angle = atan2(1. * (mp.m_ny - sp.m_ny), (sp.m_nx - mp.m_nx));
	double sweep_angle = atan2(1. * (mp.m_ny - fp.m_ny), (fp.m_nx - mp.m_nx));
	double Radius = sqrt(pow(fp.m_nx - mp.m_nx, 2) + pow(fp.m_ny - mp.m_ny, 2));

	m_dc->Arc(mp.m_nx - Radius, mp.m_ny - Radius, mp.m_nx + Radius, mp.m_ny + Radius, mp.m_nx + Radius * cos(sp_angle),
		mp.m_ny - Radius * sin(sp_angle), mp.m_nx + Radius * cos(sweep_angle), mp.m_ny - Radius * sin(sweep_angle));
}

