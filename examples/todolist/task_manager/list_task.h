#pragma once

#include "todolist/q/projections.pb.h"
#include "todolist/attributes.pb.h"
#include "tclap/CmdLine.h"

#include <memory>
#include <functional>

class ConsoleView;
class CommandHandler;

class ListTask
{

public:

	void load_task_menu();

	ListTask(
			std::shared_ptr<ConsoleView> console_view
		,	std::shared_ptr<CommandHandler> command_handler
	);

private:

	void show_task_info(int taskId);
	void load_tasks();

private:

	std::vector<spine::examples::todolist::TaskItem> task_items_;

	std::shared_ptr<ConsoleView> console_view_;
	std::shared_ptr<CommandHandler> command_handler_;
};