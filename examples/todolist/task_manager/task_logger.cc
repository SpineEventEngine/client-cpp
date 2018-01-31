#include "task_logger.h"
#include <iostream>

void TaskLogger::print_main_menu_help()
{
	std::cout << "----------------" << std::endl;
	std::cout << std::endl;
	std::cout
		<< "(c) Create task\n"
		<< "(l) List tasks\n"
		<< "(q) Quit the programm\n";

	std::cout << std::endl;
	std::cout << "----------------" << std::endl;

	std::cout << std::endl;
}

void TaskLogger::print_back_option()
{
	std::cout << "(b) " << "Back" << std::endl;
	std::cout << "----------------" << std::endl;
}

void TaskLogger::print_task_description(spine::examples::todolist::TaskItem & task_item)
{
	std::cout << "My task details:\n";
	std::cout << "----------------" << std::endl;

	std::cout << "Description: " << task_item.description().value() << std::endl;
	std::cout << "Priority: " << spine::examples::todolist::TaskPriority_Name(task_item.priority()) << std::endl;
	std::cout << "Due date: " << "default" << std::endl;
}

void TaskLogger::print_undefined_action_message()
{
	std::cout << "There is no action with specified shortcut or argument is invalid\n";
}

void TaskLogger::print_select_an_action_prompt()
{
	std::cout << "Select an action (?)" << std::endl;
}