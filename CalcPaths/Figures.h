#pragma once
#include <memory>

#include "xml/tinyxml2.h"

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
	virtual Type GetType() const = 0;
	virtual double GetLength() const = 0;
	static Point GetPoint(tinyxml2::XMLElement* point);
	static int GetValue(tinyxml2::XMLElement* value);
	virtual void Draw() const = 0;
};



