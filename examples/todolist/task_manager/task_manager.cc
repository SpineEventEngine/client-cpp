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

#include "Poco/UUIDGenerator.h"

namespace spine {
namespace examples {
namespace todolist {

const std::string CHANNEL = "localhost:50051";

TaskManager::TaskManager(const std::string & path_to_exec_file)
	:	console_view_(new ConsoleViewImpl(path_to_exec_file))
	,	command_handler_( new CommandHandlerImpl(CHANNEL))
{
}

void TaskManager::initialize_tasks()
{
	console_view_->add_simple_command(
		ConsoleCommandType::CREATE_TASK,
		std::make_shared<TCLAP::SwitchArg>("c", "create_task", "Create task", false)
	);

	console_view_->add_simple_command(
		ConsoleCommandType::LIST_TASK,
		std::make_shared<TCLAP::SwitchArg>("l", "task_list", "Print tasks list", false)
	);

	console_view_->add_simple_command(
		ConsoleCommandType::QUIT_PROGRAM,
		std::make_shared<TCLAP::SwitchArg>("q", "quit_task", "Quit tasks list", false)
	);
}

void TaskManager::start()
{
	std::cout << "Main menu" << std::endl;

	console_view_->activate_console([&]()
	{
		console_view_->reset_tasks();

		ConsoleWriter::print_main_menu_help();

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
			ConsoleWriter::print_undefined_action_message();
		}

		return true;
	});
}

void TaskManager::add_task() {
	std::cout << "Please enter the task description\n";
	std::string description;
	std::getline(std::cin, description);

	auto create_task_command = std::make_unique<CreateTask>(command_handler_);
	std::string task_identifier = generate_task_id();

	try {
		create_task_command->post(task_identifier, description);
		std::cout << "Task created\n";
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

std::string TaskManager::generate_task_id()
{
	Poco::UUIDGenerator generator;
	return generator.createRandom().toString();
}

} // namespace todolist
} // namespace examples
} // namespace spine
