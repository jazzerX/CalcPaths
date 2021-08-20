#include "pch.h"
#include "Path.h"


double Path::CheckBelongs(Point pos)
{
	for (auto& path : m_path)
		if (path->BelongFigure(pos))
			return path->GetLength();

	return -1;
}