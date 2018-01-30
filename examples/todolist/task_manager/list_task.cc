#include "list_task.hpp"
#include "task_logger.hpp"

#include "todolist/model.pb.h"

#include "console_view/console_view_impl.h"
#include "command_handler/command_handler.hpp"


ListTask::ListTask(
		std::shared_ptr<ConsoleView> console_view
	,	std::shared_ptr<CommandHandler> command_handler
)
	: console_view_(console_view)
	, command_handler_(command_handler)
{
	console_view_->add_simple_command(
		ConsoleCommandType::BACK_TO_PREVIOUS_MENU
		, std::make_shared<TCLAP::SwitchArg>(new TCLAP::SwitchArg("b", "Back", "Go to previous menu", false))
	);
}

void ListTask::load_tasks()
{
	auto const & taskListView = CommandHandler::getCommandHandler().getTasks();

	for (int i = 0; i < taskListView.items_size(); i++)
		task_items_.push_back(taskListView.items(i));
}

void ListTask::load_task_menu()
{
	console_view_->activate_console([&]()
	{
		std::cout << "My tasks list:\n" << std::endl;
		std::cout << "----------------" << std::endl;

		load_tasks();

		console_view_->reset_task_view_commands();

		for (int index = 0; index < task_items_.size(); ++index)
		{
			std::string taskIndex = std::to_string(index + 1);
			std::cout << "(" << std::to_string(index + 1) << ") " << task_items_[index].description().value() << "\n";

			console_view_->add_task_view_command(
				std::make_shared<TCLAP::SwitchArg>(new TCLAP::SwitchArg(taskIndex, "task number " + taskIndex, "Choose task " + taskIndex, false))
			);
		}

		TaskLogger::print_back_option();
		TaskLogger::print_select_an_action_prompt();

		console_view_->run_command_input();

		int active_task_number = -1;
		if (console_view_->is_task_set(active_task_number))
		{
			show_task_info(active_task_number);
		}
		else if (console_view_->is_command_set(ConsoleCommandType::BACK_TO_PREVIOUS_MENU))
		{
			return false;
		}

		TaskLogger::print_undefined_action_message();
		return true;
	});	
}

void ListTask::show_task_info(int active_task_number)
{
	assert(active_task_number == -1);

	auto & taskItem = task_items_[active_task_number];

	TaskLogger::print_task_description(taskItem);

	console_view_->activate_console([&] ()
	{
		TaskLogger::print_back_option();
		TaskLogger::print_select_an_action_prompt();

		console_view_->run_command_input();
		if (console_view_->is_command_set(ConsoleCommandType::BACK_TO_PREVIOUS_MENU))
		{
			return false;
		}

		TaskLogger::print_undefined_action_message();
		return true;
	});
}

