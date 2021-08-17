#include "pch.h"
#include "BuildPaths.h"

#include <cfloat>


std::shared_ptr<Path> CShortestPath::MakePath(std::list<Path>& listPaths)
{
	double nMinLength = DBL_MAX;
	double nCurrLength;
	std::shared_ptr<Path> res = nullptr;
	for (auto& objs : listPaths)
	{
		nCurrLength = 0;
		for (const auto& path : objs)
			nCurrLength += path->GetLength();

		if (nCurrLength < nMinLength)
		{
			nMinLength = nCurrLength;
			res = std::make_shared<Path>(objs);
		}
	}
	return res;
}

std::shared_ptr<Path> CLongestPath::MakePath(std::list<Path>& listPaths)
{
	double nMaxLength = DBL_MIN;
	double nCurrLength;
	std::shared_ptr<Path> res = nullptr;
	for (auto& objs : listPaths)
	{
		nCurrLength = 0;
		for (auto& path : objs)
			nCurrLength += path->GetLength();

		if (nCurrLength > nMaxLength)
		{
			nMaxLength = nCurrLength;
			res = std::make_shared<Path>(objs);
		}
	}
	return res;
}

std::shared_ptr<Path> COnlyLines::MakePath(std::list<Path>& listPaths)
{
	std::shared_ptr<Path> res = nullptr;

	for (auto& objs : listPaths)
	{
		bool bIsLines = true;
		for (auto& path : objs)
			if (path->GetType() != Type::LineSegment)
			{
				bIsLines = false;
				break;
			}

		if (bIsLines) 
			res = std::make_shared<Path>(objs);
	}

	return res;
}

std::shared_ptr<Path> COnlyArcs::MakePath(std::list<Path>& listPaths)
{
	std::shared_ptr<Path> res = nullptr;
	
	for (auto& objs : listPaths)
	{
		bool bIsArcs = true;
		for (auto& path : objs)
			if (path->GetType() != Type::Arc)
			{
				bIsArcs = false;
				break;
			}

		if (bIsArcs)
			res = std::make_shared<Path>(objs);
	}

	return res;
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

std::shared_ptr<Path> CTask::Run(std::list<Path>& listPaths)
{
	return m_buildPath->MakePath(listPaths);
}