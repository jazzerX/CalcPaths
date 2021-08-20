#include "pch.h"
#include "LineSegment.h"
#include "gdidrawer.h"


CLineSegment::CLineSegment(Point startPoint, Point finishPoint, Type type)
{
	m_startPoint = startPoint;
	m_finishPoint = finishPoint;

	m_type = type;

	m_dblLength = sqrt(pow(m_finishPoint.m_nx - m_startPoint.m_nx, 2) + pow(m_finishPoint.m_ny - m_startPoint.m_ny, 2));
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
	if (point != nullptr)
	{
		tinyxml2::XMLElement* pointList = point->ToElement();

		Point res;

		res.m_nx = GetValue(pointList->FirstChildElement("x"));
		res.m_ny = GetValue(pointList->FirstChildElement("y"));

		return res;
	}
	else
	{
		throw _T("Документ не валидный");
	}
}

CLineSegment CLineSegment::GetLine(tinyxml2::XMLElement* figure)
{
	if (figure != nullptr)
	{
		Point sp, fp;
		tinyxml2::XMLElement* pointList = figure->ToElement();

		sp = GetPoint(pointList->FirstChildElement("StartPoint"));
		fp = GetPoint(pointList->FirstChildElement("FinishPoint"));

		return CLineSegment(sp, fp, Type::LineSegment);
	}
	else
	{
		throw _T("Документ не валидный");
	}
}


void CLineSegment::Draw(std::unique_ptr<IDrawer>& drawer) const
{
	drawer->DrawLine(m_startPoint, m_finishPoint);
}

bool CLineSegment::BelongFigure(Point pos)
{
	double l1 = sqrt(pow(pos.m_nx - m_startPoint.m_nx, 2) + pow(pos.m_ny - m_startPoint.m_ny, 2));
	double l2 = sqrt(pow(pos.m_nx - m_finishPoint.m_nx, 2) + pow(pos.m_ny - m_finishPoint.m_ny, 2));

	const double d = 0.2;

	if (abs(m_dblLength - (l1 + l2)) <= d)
		return true;

	return false;
}
