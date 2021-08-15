#include "pch.h"
#include "Figures.h"

#include <cmath>

// Реализация методов для LineSegment

CLineSegment::CLineSegment(Point& startPoint, Point& finishPoint, Type type)
{
	this->m_StartPoint = std::make_unique<Point>(startPoint);
	this->m_FinishPoint = std::make_unique<Point>(finishPoint);

	this->m_Type = type;

	this->m_dblLength = std::sqrt(pow(m_FinishPoint->m_nx - m_StartPoint->m_nx, 2) + pow(m_FinishPoint->m_ny - m_StartPoint->m_ny, 2));
}

Type CLineSegment::GetType()
{
	return this->m_Type;
}

double CLineSegment::Length()
{
	return m_dblLength;
}


void CLineSegment::Draw()
{

}

// Реализация методов для CArc

double CArc::CalcLength()
{
	double r = sqrt(pow(m_MiddlePoint->m_nx - m_StartPoint->m_nx, 2) + pow(m_MiddlePoint->m_ny - m_StartPoint->m_ny, 2));
	Point v1, v2;
	v1.m_nx = m_MiddlePoint->m_nx - m_StartPoint->m_nx;
	v1.m_ny = m_MiddlePoint->m_ny - m_StartPoint->m_ny;
	v2.m_nx = m_MiddlePoint->m_nx - m_FinishPoint->m_nx;
	v2.m_ny = m_MiddlePoint->m_ny - m_FinishPoint->m_ny;
	double angle = acos((v1.m_nx * v2.m_nx - v1.m_ny * v2.m_ny) / (sqrt(v1.m_nx * v1.m_nx + v1.m_ny * v1.m_ny) * sqrt(v2.m_nx * v2.m_nx + v2.m_ny * v2.m_ny)));
	return r * angle;
}

CArc::CArc(Point& startPoint, Point& middlePoint, Point& finishPoint, Type type)
{
	this->m_StartPoint = std::make_unique<Point>(startPoint);
	this->m_MiddlePoint = std::make_unique<Point>(middlePoint);
	this->m_FinishPoint = std::make_unique<Point>(finishPoint);

	this->m_Type = type;

	this->m_dblLength = CalcLength();
}

Type CArc::GetType()
{
	return this->m_Type;
}

double CArc::Length()
{
	return this->m_dblLength;
}

void CArc::Draw()
{

}
