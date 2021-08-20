#pragma once

#include <list>

#include "Figures.h"

using FigurePtr = std::unique_ptr<IFigure>;

struct Path
{
	std::list<FigurePtr> m_path;

	double CheckBelongs(Point pos);
};

using PathPtr = std::weak_ptr<Path>;