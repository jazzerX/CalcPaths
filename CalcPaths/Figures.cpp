#include "pch.h"
#include "Figures.h"

#include <cmath>

// Реализация методов для LineSegment

CLineSegment::CLineSegment(Point startPoint, Point finishPoint, Type type)
{
	this->m_startPoint = startPoint;
	this->m_finishPoint = finishPoint;

	this->m_type = type;

	this->m_dblLength = std::sqrt(pow(m_finishPoint.m_nx - m_startPoint.m_nx, 2) + pow(m_finishPoint.m_ny - m_startPoint.m_ny, 2));
}

Type CLineSegment::GetType()
{
	return this->m_type;
}

double CLineSegment::Length()
{
	return  this->m_dblLength;
}


void CLineSegment::Draw()
{

}

// Реализация методов для CArc

CArc::CArc(Point startPoint, Point middlePoint, Point finishPoint, Type type)
{
	this->m_startPoint = startPoint;
	this->m_middlePoint = middlePoint;
	this->m_finishPoint = finishPoint;

	this->m_type = type;

	this->m_dblLength = CalcLength();
}

double CArc::CalcLength()
{
	double r = sqrt(pow(m_middlePoint.m_nx - m_startPoint.m_nx, 2) + pow(m_middlePoint.m_ny - m_startPoint.m_ny, 2));
	Point v1, v2;
	v1.m_nx = m_middlePoint.m_nx - m_startPoint.m_nx;
	v1.m_ny = m_middlePoint.m_ny - m_startPoint.m_ny;
	v2.m_nx = m_middlePoint.m_nx - m_finishPoint.m_nx;
	v2.m_ny = m_middlePoint.m_ny - m_finishPoint.m_ny;
	double angle = acos((v1.m_nx * v2.m_nx - v1.m_ny * v2.m_ny) / (sqrt(v1.m_nx * v1.m_nx + v1.m_ny * v1.m_ny) * sqrt(v2.m_nx * v2.m_nx + v2.m_ny * v2.m_ny)));
	return r * angle;
}


double CArc::Length()
{
	return this->m_dblLength;
}

Type CArc::GetType()
{
	return this->m_type;
}


void CArc::Draw()
{

}
