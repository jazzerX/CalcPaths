#include "pch.h"
#include "BuildPaths.h"

#include <cfloat>


Path CShortestPath::MakePath(std::vector<Path> vecPaths)
{
	double nMinLength = DBL_MAX;
	int nMinIdx = 0;
	double nCurrLength;

	for (size_t i = 0; i < vecPaths.size(); i++)
	{
		nCurrLength = 0;
		for (size_t j = 0; j < vecPaths[i].size(); j++)
			nCurrLength += vecPaths[i][j]->Length();

		if (nCurrLength < nMinLength)
		{
			nMinLength = nCurrLength;
			nMinIdx = i;
		}
	}

	return std::move(vecPaths[nMinIdx]);
}

Path CLongestPath::MakePath(std::vector<Path> vecPaths)
{
	double nMaxLength = DBL_MIN;
	int nMaxIdx = 0;
	double nCurrLength;

	for (size_t i = 0; i < vecPaths.size(); i++)
	{
		nCurrLength = 0;
		for (size_t j = 0; j < vecPaths[i].size(); j++)
			nCurrLength += vecPaths[i][j]->Length();

		if (nCurrLength > nMaxLength)
		{
			nMaxLength = nCurrLength;
			nMaxIdx = i;
		}
	}

	return std::move(vecPaths[nMaxIdx]);
}

Path COnlyLines::MakePath(std::vector<Path> vecPaths)
{
	Path resPath;

	for (size_t i = 0; i < vecPaths.size(); i++)
		for (size_t j = 0; j < vecPaths[i].size(); j++)
			if (vecPaths[i][j]->GetType() == Type::LineSegment)
				resPath.push_back(vecPaths[i][j]);

	return std::move(resPath);
}

Path COnlyArcs::MakePath(std::vector<Path> vecPaths)
{
	Path resPath;

	for (size_t i = 0; i < vecPaths.size(); i++)
		for (size_t j = 0; j < vecPaths[i].size(); j++)
			if (vecPaths[i][j]->GetType() == Type::Arc)
				resPath.push_back(vecPaths[i][j]);

	return std::move(resPath);
}

CTask::CTask(std::shared_ptr<IBuildPath> path)
{
	this->m_BuildPath = std::move(path);
}

CTask::~CTask()
{
	m_BuildPath.~shared_ptr();
}

void CTask::SetStrategy(std::shared_ptr<IBuildPath> path)
{
	m_BuildPath.~shared_ptr();
	this->m_BuildPath = std::move(path);
}

Path CTask::DoAlgorithm(std::vector<Path> vecPaths)
{
	return this->m_BuildPath->MakePath(std::move(vecPaths));
}



