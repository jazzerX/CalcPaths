#include "pch.h"
#include "Arc.h"

constexpr double g_dblPI = 3.14159265358979323846264338327950288;

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
	double r = sqrt(pow(m_middlePoint.m_nx - m_startPoint.m_nx, 2) + pow(m_middlePoint.m_ny - m_startPoint.m_ny, 2));

	Point v1, v2;
	v1.m_nx = m_startPoint.m_nx - m_middlePoint.m_nx;
	v1.m_ny = m_startPoint.m_ny - m_middlePoint.m_ny;

	v2.m_nx = m_finishPoint.m_nx - m_middlePoint.m_nx;
	v2.m_ny = m_finishPoint.m_ny - m_middlePoint.m_ny;

	double angle = acos((v1.m_nx * v2.m_nx + v1.m_ny * v2.m_ny) / (sqrt(v1.m_nx * v1.m_nx + v1.m_ny * v1.m_ny) * sqrt(v2.m_nx * v2.m_nx + v2.m_ny * v2.m_ny)));
	
	if (m_startPoint.m_nx < m_finishPoint.m_nx)
		return r * angle;
	else
		return 2 * g_dblPI * r - (r * angle);
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
		throw _T("Документ не валидный");
	}
}

Point CArc::GetPoint(tinyxml2::XMLElement* point)
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


Type CArc::GetType() const
{
	return m_type;
}


void CArc::Draw(std::unique_ptr<IDrawer>& drawer) const
{
	drawer->DrawArc(m_startPoint, m_middlePoint, m_finishPoint);
}

bool CArc::BelongFigure(Point pos)
{
	double r = sqrt(pow(m_middlePoint.m_nx - pos.m_nx, 2) + pow(m_middlePoint.m_ny - pos.m_ny, 2));
	double r1 = sqrt(pow(m_middlePoint.m_nx - m_startPoint.m_nx, 2) + pow(m_middlePoint.m_ny - m_startPoint.m_ny, 2));

	if (abs(r - r1) <= 5)
	{
		double dblSpAngle = atan2(1. * (m_middlePoint.m_ny - m_startPoint.m_ny), (m_startPoint.m_nx - m_middlePoint.m_nx));
		double dblSweepAngle = atan2(1. * (m_middlePoint.m_ny - m_finishPoint.m_ny), (m_finishPoint.m_nx - m_middlePoint.m_nx));
		double dblTmpAngle = atan2(1. * (m_middlePoint.m_ny - pos.m_ny), (pos.m_nx - m_middlePoint.m_nx));

		if (dblSpAngle < dblTmpAngle)
			return true;
	}

	return false;
}

CArc CArc::GetLine(tinyxml2::XMLElement* figure)
{
	if (figure != nullptr)
	{
		Point m_startPoint, m_middlePoint, m_finishPoint;
		tinyxml2::XMLElement* pointList = figure->ToElement();

		m_startPoint = CArc::GetPoint(pointList->FirstChildElement("StartPoint"));
		m_middlePoint = CArc::GetPoint(pointList->FirstChildElement("CenterPoint"));
		m_finishPoint = CArc::GetPoint(pointList->FirstChildElement("FinishPoint"));

		return CArc(m_startPoint, m_middlePoint, m_finishPoint, Type::Arc);
	}
	else
	{
		throw _T("Документ не валидный");
	}
}
