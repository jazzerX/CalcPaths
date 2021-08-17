#include "pch.h"
#include "LineSegment.h"

CLineSegment::CLineSegment(Point startPoint, Point finishPoint, Type type)
{
	m_startPoint = startPoint;
	m_finishPoint = finishPoint;

	m_type = type;

	m_dblLength = ::sqrt(::pow(m_finishPoint.m_nx - m_startPoint.m_nx, 2) + ::pow(m_finishPoint.m_ny - m_startPoint.m_ny, 2));
}

Type CLineSegment::GetType() const
{
	return m_type;
}

double CLineSegment::GetLength() const
{
	return  m_dblLength;
}

int CLineSegment::GetValue(tinyxml2::XMLElement* value)
{
	if (value != nullptr)
	{
		tinyxml2::XMLElement* valueList = value->ToElement();
		return value->IntText();
	}
	else
	{
		throw _T("Документ не валидный");
	}
}

Point CLineSegment::GetPoint(tinyxml2::XMLElement* point)
{
	tinyxml2::XMLElement* pointList = point->ToElement();
	Point res;

	res.m_nx = GetValue(pointList->FirstChildElement("x"));
	res.m_ny = GetValue(pointList->FirstChildElement("y"));

	return res;
}




void CLineSegment::Draw() const
{

}