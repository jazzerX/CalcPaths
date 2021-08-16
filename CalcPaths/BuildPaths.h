#pragma once

#include "Figures.h"
#include <vector>

using Path = std::vector<std::shared_ptr<IFigure>>;

// Реализация паттерна проектирования "Стратегия"

// Интерфейс
class IBuildPath
{
public:
	virtual Path MakePath(std::vector<Path>) = 0; 
};

// Классы, реализующие построение путей
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

// Класс, отвечающий за переключение и запуск стратегии
class CTask 
{
private:
	std::shared_ptr<IBuildPath> m_buildPath;

public:
	CTask(std::shared_ptr<IBuildPath> path);
	~CTask();

	void SetStrategy(std::shared_ptr<IBuildPath> path);
	Path Run(std::vector<Path>);
};
