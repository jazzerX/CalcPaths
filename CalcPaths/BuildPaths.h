#pragma once

#include "Figures.h"
#include <vector>

using Path = std::vector<std::shared_ptr<IFigure>>;


class IBuildPath
{
public:
	virtual Path MakePath(std::vector<Path>) = 0; 
};

class CShortestPath : public IBuildPath
{
	virtual Path MakePath(std::vector<Path>) override;
};

class CLongestPath : public IBuildPath
{
	virtual Path MakePath(std::vector<Path>) override;
};

class COnlyLines : public IBuildPath
{
	virtual Path MakePath(std::vector<Path>) override;
};

class COnlyArcs : public IBuildPath
{
	virtual Path MakePath(std::vector<Path>) override;
};

class CTask 
{
private:
	std::shared_ptr<IBuildPath> m_BuildPath;

public:
	CTask(std::shared_ptr<IBuildPath> path);
	~CTask();

	void SetStrategy(std::shared_ptr<IBuildPath> path);
	Path DoAlgorithm(std::vector<Path>);
};
