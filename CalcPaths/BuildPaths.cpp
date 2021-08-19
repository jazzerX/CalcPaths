#include "pch.h"
#include "BuildPaths.h"

#include <cfloat>




std::list<PathPtr> ShortestPath::MakePath(std::list<std::shared_ptr<Path>>& listPaths)
{
	double dblMinLength = DBL_MAX;
	double dblCurrLength;

	std::list<PathPtr> res;
	std::weak_ptr<Path> minPath;

	for (auto& objs : listPaths)
	{
		dblCurrLength = 0;
		for (const auto& path : objs->m_path)
			dblCurrLength += path->GetLength();

		if (dblCurrLength <= dblMinLength)
		{
			dblMinLength = dblCurrLength;
			res.emplace_back(objs);
		}
	}

	res.emplace_back(minPath);

	return res;
}

std::list<PathPtr> LongestPath::MakePath(std::list<std::shared_ptr<Path>>& listPaths)
{
	double dblMaxLength = DBL_MIN;
	double dblCurrLength;

	std::list<PathPtr> res;
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

std::list<PathPtr> OnlyLines::MakePath(std::list<std::shared_ptr<Path>>& listPaths)
{
	std::list<PathPtr> res;

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

std::list<PathPtr> OnlyArcs::MakePath(std::list<std::shared_ptr<Path>>& listPaths)
{
	std::list<PathPtr> res;
	
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


std::list<PathPtr> AllPaths::MakePath(std::list<std::shared_ptr<Path>>& listPaths)
{

	std::list<PathPtr> res;
	for (auto& objs : listPaths)
		res.emplace_back(objs);

	return res;
}


Task::Task(std::unique_ptr<IBuildPath> path)
{
	m_buildPath = std::move(path);
}

void Task::SetStrategy(std::unique_ptr<IBuildPath> path)
{
	m_buildPath.~unique_ptr();
	m_buildPath = std::move(path);
}

std::list<PathPtr> Task::Run(std::list<std::shared_ptr<Path>>& listPaths)
{
	return m_buildPath->MakePath(listPaths);
}

