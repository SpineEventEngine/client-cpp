#include "console_view_impl.h"
#include "task_manager/task_logger.h"

ConsoleViewImpl::ConsoleViewImpl(std::string const & _path_to_exec_file)
	:	command_handler_(new TCLAP::CmdLine("Command description message", ' ', "0.9", false))
	,	path_to_exec_file_(_path_to_exec_file)
{
	command_handler_->setExceptionHandling(false);
}

void ConsoleViewImpl::add_simple_command(ConsoleCommandType command_type, std::shared_ptr<TCLAP::SwitchArg> command_args)
{
	commands_[command_type] = command_args;
	command_handler_->add(command_args.get());
}

void ConsoleViewImpl::add_task_view_command(std::shared_ptr<TCLAP::SwitchArg> command_args)
{
	task_commands_.push_back(command_args);
	command_handler_->add(command_args.get());
}

void ConsoleViewImpl::reset_tasks()
{
	task_commands_.clear();
	commands_.clear();
	command_handler_->resetTasks();
}

void ConsoleViewImpl::run_command_input()
{
	TaskLogger::print_select_an_action_prompt();
	std::string line;
	std::getline(std::cin, line);
	std::string command = "-" + line;
	std::istringstream iss(command);
	std::vector<std::string> inputStrings;
	inputStrings.push_back(path_to_exec_file_);

	for (std::string word; iss >> word;) {
		inputStrings.push_back(word);
	}

	command_handler_->parse(inputStrings);
}

void ConsoleViewImpl::activate_console(std::function<bool()> _callback)
{
	do
	{
		try
		{
			if (!_callback())
			{
				break;
			}
		}
		catch (TCLAP::ArgException &e)
		{
			TaskLogger::print_undefined_action_message();
		}

	} while (true);
}

bool ConsoleViewImpl::is_command_set(ConsoleCommandType command_type)
{
	std::shared_ptr<TCLAP::SwitchArg> command = commands_[command_type];
	return command->isSet();
}

bool ConsoleViewImpl::is_task_set(int & active_task_number) const
{
	for (int task_index = 0; task_index < task_commands_.size(); ++task_index)
	{
		auto task_command = task_commands_[task_index];
		if (task_command->isSet())
		{
			active_task_number = task_index;
			return true;
		}

	}

	return false;
}