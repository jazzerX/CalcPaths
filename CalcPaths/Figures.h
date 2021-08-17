#pragma once
#include <memory>

#include "Drawer.h"

#include "xml/tinyxml2.h"

// ���������� �������� �������������� "��������� �����"

enum class Type { LineSegment, Arc };


class IFigure
{
public:
	virtual Type GetType() const = 0;
	virtual double GetLength() const = 0;
	virtual void Draw(std::unique_ptr<IDrawer>& drawer) const = 0;
};



