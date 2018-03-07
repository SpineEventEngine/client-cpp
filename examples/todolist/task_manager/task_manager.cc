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

#include "task_manager.h"
#include "create_task.h"
#include "list_task.h"
#include "console_view/console_writer.h"
#include "console_view/console_view_impl.h"
#include "command_handler/command_handler_impl.h"
#include "resources/resources.h"

namespace spine {
namespace examples {
namespace todolist {

TaskManager::TaskManager(const std::string & path_to_exec_file)
	:	console_view_(new ConsoleViewImpl(path_to_exec_file))
	,	command_handler_( new CommandHandlerImpl(resources::server_info::CHANNEL))
{
}

void TaskManager::start()
{
	console_view_->activate_console([&]()
	{
		std::cout << resources::messages::MAIN_MENU << std::endl;
		std::cout << resources::command_line::LINE_SEPARATOR << std::endl;
		
		initialize_commands();
		return process_command();
	});
}

void TaskManager::initialize_commands()
{
	console_view_->add_simple_command(
		ConsoleCommandType::CREATE_TASK,
		resources::tasks_menu::CREATE_TASK_SHORTCUT,
		resources::tasks_menu::CREATE_TASK_COMMAND,
		resources::tasks_menu::CREATE_TASK_INFO
	);

	console_view_->add_simple_command(
		ConsoleCommandType::LIST_TASK,
		resources::tasks_menu::LIST_TASK_SHORTCUT,
		resources::tasks_menu::LIST_TASK_COMMAND,
		resources::tasks_menu::LIST_TASK_INFO
	);

	console_view_->add_simple_command(
		ConsoleCommandType::QUIT_PROGRAM,
		resources::tasks_menu::QUIT_TASK_SHORTCUT,
		resources::tasks_menu::QUIT_TASK_COMMAND,
		resources::tasks_menu::QUIT_TASK_INFO
	);
}

bool TaskManager::process_command()
{
	console_view_->run_command_input();
	switch (console_view_->get_active_task())
	{
		case ConsoleCommandType::CREATE_TASK:
			add_task();
			break;
		case ConsoleCommandType::LIST_TASK:
			list_tasks();
			break;
		case ConsoleCommandType::QUIT_PROGRAM:
			return false;
		default:
			ConsoleWriter::print_undefined_action_message();
	}

	return true;
}

void TaskManager::add_task() {
	auto create_task_command = std::make_unique<CreateTask>(console_view_, command_handler_);
	try {
		create_task_command->run_task_creation();
	}
	catch (std::exception & _exception)
	{
		std::cout << _exception.what() << std::endl;
	}
}

void TaskManager::list_tasks() const {

	auto list_task_command = std::make_unique<ListTask>(console_view_, command_handler_);
	try
	{
		list_task_command->load_task_menu();
	}
	catch (std::exception & _exception)
	{
		std::cout << _exception.what() << std::endl;
	}
}

} // namespace todolist
} // namespace examples
} // namespace spine
