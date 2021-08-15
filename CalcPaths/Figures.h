#pragma once
#include <memory>


enum class Type { LineSegment, Arc };

struct Point
{
	int m_nx;
	int m_ny;
};

class IFigure
{
public:
	virtual Type GetType() = 0;
	virtual double  Length() = 0;
	virtual void Draw() = 0;
};

class CLineSegment : public IFigure
{
private:
	std::unique_ptr<Point> m_StartPoint;
	std::unique_ptr<Point> m_FinishPoint;

	Type m_Type;

	double m_dblLength;

public:
	CLineSegment(Point& startPoint, Point& finishPoint, Type type);

	virtual Type GetType() override;
	virtual double Length() override;
	virtual void Draw() override;
};

class CArc : public IFigure
{
private:
	std::unique_ptr<Point> m_StartPoint;
	std::unique_ptr<Point> m_MiddlePoint;
	std::unique_ptr<Point> m_FinishPoint;
	std::unique_ptr<bool> m_bClock;

	Type m_Type;

	double m_dblLength;

public:
	CArc(Point& startPoint, Point& middlePoint, Point& finishPoint, Type type);

	virtual Type GetType() override;
	virtual double Length() override;
	virtual void Draw() override;

private:
	double CalcLength();
};

