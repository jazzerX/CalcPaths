#pragma once

#include "Figures.h"
#include <list>

struct Path
{
	std::list<std::unique_ptr<IFigure>> m_path;
};

// Реализация паттерна проектирования "Стратегия"

// Интерфейс
class IBuildPath
{
public:
	virtual std::list<std::weak_ptr<Path>> MakePath(std::list<std::shared_ptr<Path>>&) = 0;
};

// Классы, реализующие построение путей
class CShortestPath : public IBuildPath
{
	virtual std::list<std::weak_ptr<Path>> MakePath(std::list<std::shared_ptr<Path>>&) override;
};

class CLongestPath : public IBuildPath
{
	virtual std::list<std::weak_ptr<Path>> MakePath(std::list<std::shared_ptr<Path>>&) override;
};

class COnlyLines : public IBuildPath
{
	virtual std::list<std::weak_ptr<Path>> MakePath(std::list<std::shared_ptr<Path>>&) override;
};

class COnlyArcs : public IBuildPath
{
	virtual std::list<std::weak_ptr<Path>> MakePath(std::list<std::shared_ptr<Path>>&) override;
};

// Класс, отвечающий за переключение и запуск стратегии
class CTask 
{
private:
	std::unique_ptr<IBuildPath> m_buildPath;

public:
	CTask(std::unique_ptr<IBuildPath> path);

	void SetStrategy(std::unique_ptr<IBuildPath> path);
	std::list<std::weak_ptr<Path>> Run(std::list<std::shared_ptr<Path>>&);
};
