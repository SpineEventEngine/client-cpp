#pragma once

#include "tclap/CmdLine.h"

#include <string>
#include <memory>

class TaskManager final
{

public:

	TaskManager();
	~TaskManager() = default;

	void init() noexcept;
	void start(std::string const & _pathToExecFile);

private:

	void addTask() noexcept;
	void listTasks() const noexcept;
	void printHelp() const noexcept;

private:

	std::unique_ptr<TCLAP::CmdLine> m_commandHandler;

	TCLAP::SwitchArg m_createTaskParams;
	TCLAP::SwitchArg m_listTasksParams;
	TCLAP::SwitchArg m_quitTaskParams;
};