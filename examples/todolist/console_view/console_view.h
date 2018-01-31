#pragma once

#include <functional>
#include <memory>
#include "tclap/SwitchArg.h"

enum class ConsoleCommandType
{
	CREATE_TASK,
	LIST_TASK,
	VIEW_TASK,
	BACK_TO_PREVIOUS_MENU,
	QUIT_PROGRAM
};

class ConsoleView
{

public:

	virtual ~ConsoleView() {}

	virtual void add_simple_command(ConsoleCommandType command_type, std::shared_ptr<TCLAP::SwitchArg> command_args) = 0;
	virtual void add_task_view_command(std::shared_ptr<TCLAP::SwitchArg> command_args) = 0;
	virtual void run_command_input() = 0;

	virtual void activate_console(std::function<bool()> _callback) = 0;
	virtual void reset_task_view_commands() = 0;

	virtual bool is_command_set(ConsoleCommandType command_type) = 0;
	virtual bool is_task_set(int & active_task_number) const = 0;
};