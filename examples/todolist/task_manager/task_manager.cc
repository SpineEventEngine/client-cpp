#pragma once

#include "task_manager.h"
#include "create_task.h"
#include "list_task.h"
#include "task_logger.h"
#include "console_view/console_view_impl.h"
#include "command_handler/command_handler_impl.h"

#include "Poco/UUIDGenerator.h"

TaskManager::TaskManager(std::string const & path_to_exec_file)
	:	console_view_(new ConsoleViewImpl(path_to_exec_file))
	,	command_handler_( new CommandHandlerImpl())
{
}

void TaskManager::initialize_tasks() noexcept
{
	console_view_->add_simple_command(
			ConsoleCommandType::CREATE_TASK
		,	std::make_shared<TCLAP::SwitchArg>("c", "create_task", "Create task", false)
	);

	console_view_->add_simple_command(
			ConsoleCommandType::LIST_TASK
		,	std::make_shared<TCLAP::SwitchArg>("l", "task_list", "Print tasks list", false)
	);

	console_view_->add_simple_command(
			ConsoleCommandType::QUIT_PROGRAM
		,	std::make_shared<TCLAP::SwitchArg>("q", "quit_task", "Quit tasks list", false)
	);
}

void TaskManager::start()
{
	std::cout << "Main menu" << std::endl;
	std::cout << std::endl;

	console_view_->activate_console([&]()
	{
		console_view_->reset_tasks();

		TaskLogger::print_main_menu_help();

		initialize_tasks();

		console_view_->run_command_input();

		if (console_view_->is_command_set(ConsoleCommandType::CREATE_TASK)) {
			add_task();
		}
		else if (console_view_->is_command_set(ConsoleCommandType::LIST_TASK)) {
			list_tasks();
		}
		else if (console_view_->is_command_set(ConsoleCommandType::QUIT_PROGRAM)) {
			return false;
		}
		else {
			TaskLogger::print_undefined_action_message();
		}

		return true;
	});
}

void TaskManager::add_task() {
	std::cout << "Please enter the task description\n";
	std::string description;
	std::getline(std::cin, description);

	auto createTaskCommand = std::make_unique<CreateTask>(command_handler_);
	std::string task_identifier = generate_task_id();

	try {
		createTaskCommand->post(task_identifier, description);
		std::cout << "Task created\n";
	}
	catch (std::exception & _exception)
	{
		std::cout << _exception.what() << std::endl;
	}
}

void TaskManager::list_tasks() const {

	auto listTaskCommand
		= std::make_unique<ListTask>(console_view_, command_handler_);

	try
	{
		listTaskCommand->load_task_menu();
	}
	catch (std::exception & _exception)
	{
		std::cout << _exception.what() << std::endl;
	}
}

std::string TaskManager::generate_task_id()
{
	Poco::UUIDGenerator generator;
	return generator.createRandom().toString();
}