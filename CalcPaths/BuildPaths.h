#pragma once

#include "Figures.h"
#include <list>

using FigurePtr = std::unique_ptr<IFigure>;

struct Path
{
	std::list<FigurePtr> m_path;
};

using PathPtr = std::weak_ptr<Path>;

// Реализация паттерна проектирования "Стратегия"

// Интерфейс
class IBuildPath
{
public:
	virtual std::list<PathPtr> MakePath(std::list<std::shared_ptr<Path>>&) = 0;
};

// Классы, реализующие построение путей
class ShortestPath : public IBuildPath
{
	virtual std::list<PathPtr> MakePath(std::list<std::shared_ptr<Path>>&) override;
};

class LongestPath : public IBuildPath
{
	virtual std::list<PathPtr> MakePath(std::list<std::shared_ptr<Path>>&) override;
};

class OnlyLines : public IBuildPath
{
	virtual std::list<PathPtr> MakePath(std::list<std::shared_ptr<Path>>&) override;
};

class OnlyArcs : public IBuildPath
{
	virtual std::list<PathPtr> MakePath(std::list<std::shared_ptr<Path>>&) override;
};

class AllPaths : public IBuildPath
{
	virtual std::list<PathPtr> MakePath(std::list<std::shared_ptr<Path>>&) override;
};

// Класс, отвечающий за переключение и запуск стратегии
class Task 
{
private:
	std::unique_ptr<IBuildPath> m_buildPath;

public:
	Task(std::unique_ptr<IBuildPath> path);

	void SetStrategy(std::unique_ptr<IBuildPath> path);
	std::list<PathPtr> Run(std::list<std::shared_ptr<Path>>&);
};
