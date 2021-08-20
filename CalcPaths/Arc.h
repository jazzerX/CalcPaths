#pragma once
#include "Figures.h"

class CArc : public IFigure
{
private:
	Point m_startPoint;
	Point m_middlePoint;
	Point m_finishPoint;
	bool m_bClock;

	Type m_type;

	double m_dblLength;

public:
	CArc(Point startPoint, Point middlePoint, Point finishPoint, Type type);

	virtual Type GetType() const override;
	virtual double GetLength() const override;
	virtual void Draw(std::unique_ptr<IDrawer>& drawer) const override;
	
	virtual bool BelongFigure(Point pos) override;

	static CArc GetLine(tinyxml2::XMLElement* figure);

private:
	double CalcLength();

	static Point GetPoint(tinyxml2::XMLElement* point);
	static int GetValue(tinyxml2::XMLElement* value);
};
