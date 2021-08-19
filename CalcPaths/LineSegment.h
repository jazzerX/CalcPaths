#pragma once
#include "Figures.h"

class CLineSegment : public IFigure
{
private:
	Point m_startPoint;
	Point m_finishPoint;

	Type m_type;

	double m_dblLength;


public:
	CLineSegment(Point startPoint, Point finishPoint, Type type);

	virtual Type GetType() const override;
	virtual double GetLength() const override;
	virtual void  Draw(std::unique_ptr<IDrawer>& drawer) const override;

	static CLineSegment GetLine(tinyxml2::XMLElement* figure);

private:
	static Point GetPoint(tinyxml2::XMLElement* point);
	static int GetValue(tinyxml2::XMLElement* value);
};
