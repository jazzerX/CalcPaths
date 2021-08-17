#pragma once

#include "Figures.h"
#include <list>

using Path = std::list<std::unique_ptr<IFigure>>;

// Реализация паттерна проектирования "Стратегия"

// Интерфейс
class IBuildPath
{
public:
	virtual std::unique_ptr<Path> MakePath(std::list<Path>&) = 0;
};

// Классы, реализующие построение путей
class CShortestPath : public IBuildPath
{
	virtual std::unique_ptr<Path> MakePath(std::list<Path>&) override;
};

class CLongestPath : public IBuildPath
{
	virtual std::unique_ptr<Path> MakePath(std::list<Path>&) override;
};

class COnlyLines : public IBuildPath
{
	virtual std::unique_ptr<Path> MakePath(std::list<Path>&) override;
};

class COnlyArcs : public IBuildPath
{
	virtual std::unique_ptr<Path> MakePath(std::list<Path>&) override;
};

// Класс, отвечающий за переключение и запуск стратегии
class CTask 
{
private:
	std::unique_ptr<IBuildPath> m_buildPath;

public:
	CTask(std::unique_ptr<IBuildPath> path);

	void SetStrategy(std::unique_ptr<IBuildPath> path);
	std::unique_ptr<Path> Run(std::list<Path>&);
};
