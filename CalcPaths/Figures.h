#pragma once
#include <memory>

// Реализация паттерна проектирования "Фабричный метод"

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
	Point m_startPoint;
	Point m_finishPoint;

	Type m_type;

	double m_dblLength;

public:
	CLineSegment(Point startPoint, Point finishPoint, Type type);

	virtual Type GetType() override;
	virtual double Length() override;
	virtual void Draw() override;
};

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

	virtual Type GetType() override;
	virtual double Length() override;
	virtual void Draw() override;

private:
	double CalcLength();
};

