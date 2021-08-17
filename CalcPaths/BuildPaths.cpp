#include "pch.h"
#include "BuildPaths.h"

#include <cfloat>


std::unique_ptr<Path> CShortestPath::MakePath(std::list<Path>& listPaths)
{
	double nMinLength = DBL_MAX;
	double nCurrLength;
	std::unique_ptr<Path> res = nullptr;
	for (auto& objs : listPaths)
	{
		nCurrLength = 0;
		for (const auto& path : objs)
			nCurrLength += path->GetLength();

		if (nCurrLength < nMinLength)
		{
			nMinLength = nCurrLength;
			res = std::make_unique<Path>(std::move(objs));
		}
	}
	return std::move(res);
}

std::unique_ptr<Path> CLongestPath::MakePath(std::list<Path>& listPaths)
{
	double nMaxLength = DBL_MIN;
	double nCurrLength;
	std::unique_ptr<Path> res = nullptr;
	for (auto& objs : listPaths)
	{
		nCurrLength = 0;
		for (auto& path : objs)
			nCurrLength += path->GetLength();

		if (nCurrLength > nMaxLength)
		{
			nMaxLength = nCurrLength;
			res = std::make_unique<Path>(std::move(objs));
		}
	}
	return std::move(res);
}

std::unique_ptr<Path> COnlyLines::MakePath(std::list<Path>& listPaths)
{
	std::unique_ptr<Path> res = nullptr;
	bool bIsLines = true;
	for (auto& objs : listPaths)
	{
		for (auto& path : objs)
			if (path->GetType() != Type::LineSegment)
			{
				bIsLines = false;
				break;
			}

		if (bIsLines)
			res = std::make_unique<Path>(std::move(objs));
	}

	return std::move(res);
}

std::unique_ptr<Path> COnlyArcs::MakePath(std::list<Path>& listPaths)
{
	std::unique_ptr<Path> res = nullptr;
	bool bIsLines = true;
	for (auto& objs : listPaths)
	{
		for (auto& path : objs)
			if (path->GetType() != Type::Arc)
			{
				bIsLines = false;
				break;
			}

		if (bIsLines)
			res = std::make_unique<Path>(std::move(objs));
	}

	return std::move(res);
}

CTask::CTask(std::unique_ptr<IBuildPath> path)
{
	m_buildPath = std::move(path);
}

void CTask::SetStrategy(std::unique_ptr<IBuildPath> path)
{
	m_buildPath.~unique_ptr();
	m_buildPath = std::move(path);
}

std::unique_ptr<Path> CTask::Run(std::list<Path>& listPaths)
{
	return std::move(m_buildPath->MakePath(listPaths));
}