/*
* Copyright 2018, TeamDev Ltd. All rights reserved.
*
* Redistribution and use in source and/or binary forms, with or without
* modification, must retain the above copyright notice and the following
* disclaimer.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "console_view_impl.h"
#include "console_view/console_writer.h"
#include "resources/resources.h"

namespace spine {
namespace examples {
namespace todolist {

constexpr int INVALID_TASK_NUMBER = -1;

ConsoleViewImpl::ConsoleViewImpl(std::string const & path_to_exec_file)
	:	command_handler_(
			new TCLAP::CmdLine(
				resources::command_line::COMMAND_DESCRIPTION_MESSAGE,
				resources::command_line::WHITE_SPACE_DELIMETER,
				resources::command_line::COMMAND_LINE_VERSION,
				false
			)
		)
	,	path_to_exec_file_(path_to_exec_file)
{
	command_handler_->setExceptionHandling(false);
}

void ConsoleViewImpl::add_simple_command(
	ConsoleCommandType command_type,
	std::string const & command_shortcut,
	std::string const & command_name,
	std::string const & command_description)
{
	std::cout
		<<	resources::command_line::LEFT_BRACE +
			command_shortcut +
			resources::command_line::RIGHT_BRACE
		<< command_description
		<< std::endl;

	auto command_args
		= std::make_shared<TCLAP::SwitchArg>(
			command_shortcut,
			command_name,
			command_description,
			false
		);

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
	ConsoleWriter::print_select_an_action_prompt();
	std::string line;
	std::getline(std::cin, line);
	std::string command = resources::command_line::DASH + line;
	std::istringstream iss(command);
	std::vector<std::string> inputStrings;
	inputStrings.push_back(path_to_exec_file_);

	for (std::string word; iss >> word;)
		inputStrings.push_back(word);

	command_handler_->parse(inputStrings);
}

void ConsoleViewImpl::activate_console(std::function<bool()> callback)
{
	while(true)
	{
		try 
		{
			reset_tasks();
			if (!callback())
			{
				break;
			}
		}
		catch (const TCLAP::ArgException &e)
		{
			ConsoleWriter::print_undefined_action_message();
		}
	}
}

ConsoleCommandType ConsoleViewImpl::get_active_task()
{
	for (auto it = commands_.begin(); it != commands_.end(); ++it)
	{
		if (it->second->isSet())
			return it->first;
	}
	return ConsoleCommandType::UNKNOWN;
}

bool ConsoleViewImpl::is_task_set() const
{
	for (int task_index = 0; task_index < task_commands_.size(); ++task_index)
	{
		auto task_command = task_commands_[task_index];
		if (task_command->isSet())
			return true;
	}
	return false;
}

bool ConsoleViewImpl::is_command_set(ConsoleCommandType command_type)
{
	std::shared_ptr<TCLAP::SwitchArg> command = commands_[command_type];
	return command->isSet();
}

int ConsoleViewImpl::get_active_task_index() const
{
	for (int task_index = 0; task_index < task_commands_.size(); ++task_index)
	{
		auto task_command = task_commands_[task_index];
		if (task_command->isSet())
			return task_index;
	}
	return INVALID_TASK_NUMBER;
}

} // namespace todolist
} // namespace examples
} // namespace spine
