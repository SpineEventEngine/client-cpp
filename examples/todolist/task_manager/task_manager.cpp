#pragma once

#include "task_manager.hpp"
#include "create_task.hpp"
#include "list_task.hpp"

TaskManager::TaskManager()
	:	m_commandHandler(new TCLAP::CmdLine("Command description message", ' ', "0.9", false))
	,	m_createTaskParams("c", "create_task", "Create task", false)
	,	m_listTasksParams("l", "task_list", "Print tasks list", false)
	,	m_quitTaskParams("q", "quit_task", "Quit tasks list", false)
{
	
	m_commandHandler->setExceptionHandling(false);
}

void TaskManager::init() noexcept
{
	m_commandHandler->add(m_createTaskParams);
	m_commandHandler->add(m_listTasksParams);
	m_commandHandler->add(m_quitTaskParams);
}

void TaskManager::start(std::string const & _pathToExecFile)
{
	std::cout << "Main menu" << std::endl;
	std::cout << std::endl;

	do {
		printHelp();
		std::cout << "Select an action (?)" << std::endl;
		std::string line;
		std::getline(std::cin, line);
		std::string command = "-" + line;
		std::istringstream iss(command);
		std::vector<std::string> inputStrings;
		inputStrings.push_back(_pathToExecFile);
		for (std::string word; iss >> word;) {
			inputStrings.push_back(word);
		}
		try {
			m_commandHandler->parse(inputStrings);

			if (m_createTaskParams.isSet()) {
				addTask();
			}
			else if (m_listTasksParams.isSet()) {
				listTasks();
			}
			else if (m_quitTaskParams.isSet()) {
				break;
			}
			else {
				std::cout << "There is no action with specified shortcut or argument is invalid\n";
			}

			m_commandHandler->reset();
		}
		catch (TCLAP::ArgException &e)
		{
			std::cout << "There is no action with specified shortcut or argument is invalid\n";
			m_commandHandler->reset();
		}

	} while (true);
}


void TaskManager::addTask() noexcept {

	std::cout << "Please enter the task description\n";
	std::string description;
	std::getline(std::cin, description);

	auto createTaskCommand = CreateTask::createTask();

	try {
		createTaskCommand->post(description);
		std::cout << "Task " << description << " created\n";
	}
	catch (std::exception & _exception)
	{
		std::cout << _exception.what() << "\n";
	}
}

void TaskManager::listTasks() const noexcept {
	auto listTaskCommand = ListTask::createListTask();

	try
	{
		listTaskCommand->loadTasks();

		std::cout << "Created tasks:\n";

		listTaskCommand->forEachTask([&] (std::string const & _taskName) {
			std::cout << _taskName << "\n";
		});
	}
	catch (std::exception & _exception)
	{
		std::cout << _exception.what() << "\n";
	}
}

void TaskManager::printHelp() const noexcept  {

	std::cout << "----------------" << std::endl;
	std::cout << std::endl;
	std::cout<<"(c) Create task\n"
		<< "(l) List tasks\n"
		<< "(q) Quit the programm\n";

	std::cout << std::endl;
	std::cout << "----------------" << std::endl;

	std::cout << std::endl;
}