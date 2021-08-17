#include "pch.h"
#include "Arc.h"

CArc::CArc(Point startPoint, Point middlePoint, Point finishPoint, Type type)
{
	m_startPoint = startPoint;
	m_middlePoint = middlePoint;
	m_finishPoint = finishPoint;

	m_type = type;

	m_dblLength = CalcLength();
}

double CArc::CalcLength()
{
	double r = ::sqrt(::pow(m_middlePoint.m_nx - m_startPoint.m_nx, 2) + pow(m_middlePoint.m_ny - m_startPoint.m_ny, 2));
	Point v1, v2;
	v1.m_nx = m_middlePoint.m_nx - m_startPoint.m_nx;
	v1.m_ny = m_middlePoint.m_ny - m_startPoint.m_ny;
	v2.m_nx = m_middlePoint.m_nx - m_finishPoint.m_nx;
	v2.m_ny = m_middlePoint.m_ny - m_finishPoint.m_ny;
	double angle = ::acos((v1.m_nx * v2.m_nx - v1.m_ny * v2.m_ny) / (::sqrt(v1.m_nx * v1.m_nx + v1.m_ny * v1.m_ny) * ::sqrt(v2.m_nx * v2.m_nx + v2.m_ny * v2.m_ny)));
	return r * angle;
}


double CArc::GetLength() const
{
	return m_dblLength;
}


int CArc::GetValue(tinyxml2::XMLElement* value)
{
	if (value != nullptr)
	{
		tinyxml2::XMLElement* valueList = value->ToElement();
		return value->IntText();
	}
	else
	{
		throw _T("�������� �� ��������");
	}
}

Point CArc::GetPoint(tinyxml2::XMLElement* point)
{
	tinyxml2::XMLElement* pointList = point->ToElement();
	Point res;

	res.m_nx = GetValue(pointList->FirstChildElement("x"));
	res.m_ny = GetValue(pointList->FirstChildElement("y"));

	return res;
}


Type CArc::GetType() const
{
	return m_type;
}


void CArc::Draw() const
{

}