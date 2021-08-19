#include "pch.h"
#include "BuildPaths.h"

#include <cfloat>


std::list<std::weak_ptr<Path>> CShortestPath::MakePath(std::list<std::shared_ptr<Path>>& listPaths)
{
	double dblMinLength = DBL_MAX;
	double dblCurrLength;

	std::list<std::weak_ptr<Path>> res;
	std::weak_ptr<Path> minPath;

	for (auto& objs : listPaths)
	{
		dblCurrLength = 0;
		for (const auto& path : objs->m_path)
			dblCurrLength += path->GetLength();

		if (dblCurrLength < dblMinLength)
		{
			dblMinLength = dblCurrLength;
			minPath = objs;
		}
	}

	res.emplace_back(minPath);

	return res;
}

std::list<std::weak_ptr<Path>> CLongestPath::MakePath(std::list<std::shared_ptr<Path>>& listPaths)
{
	double dblMaxLength = DBL_MIN;
	double dblCurrLength;

	std::list<std::weak_ptr<Path>> res;
	std::weak_ptr<Path> maxPath;

	for (auto& objs : listPaths)
	{
		dblCurrLength = 0;
		for (auto& path : objs->m_path)
			dblCurrLength += path->GetLength();

		if (dblCurrLength > dblMaxLength)
		{
			dblMaxLength = dblCurrLength;
			maxPath = objs;
		}
	}

	res.emplace_back(maxPath);

	return res;
}

std::list<std::weak_ptr<Path>> COnlyLines::MakePath(std::list<std::shared_ptr<Path>>& listPaths)
{
	std::list<std::weak_ptr<Path>> res;

	for (auto& objs : listPaths)
	{
		bool bIsLines = true;
		for (auto& path : objs->m_path)
			if (path->GetType() != Type::LineSegment)
			{
				bIsLines = false;
				break;
			}

		if (bIsLines)
			res.emplace_back(objs);
	}

	return res;
}

std::list<std::weak_ptr<Path>> COnlyArcs::MakePath(std::list<std::shared_ptr<Path>>& listPaths)
{
	std::list<std::weak_ptr<Path>> res;
	
	for (auto& objs : listPaths)
	{
		bool bIsArcs = true;
		for (auto& path : objs->m_path)
			if (path->GetType() != Type::Arc)
			{
				bIsArcs = false;
				break;
			}

		if (bIsArcs)
			res.emplace_back(objs);
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

std::list<std::weak_ptr<Path>> CTask::Run(std::list<std::shared_ptr<Path>>& listPaths)
{
	return m_buildPath->MakePath(listPaths);
}