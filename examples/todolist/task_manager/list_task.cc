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


#include "list_task.h"
#include "console_view/console_writer.h"
#include "todolist/model.pb.h"
#include "console_view/console_view_impl.h"
#include "command_handler/command_handler.h"

namespace spine {
namespace examples {
namespace todolist {

ListTask::ListTask(
	std::shared_ptr<ConsoleView> console_view,
	std::shared_ptr<CommandHandler> command_handler
)
	: console_view_(console_view)
	, command_handler_(command_handler)
{
}

void ListTask::load_tasks()
{
	auto const & task_list_view = command_handler_->get_tasks();
	task_items_.clear();

	for (int i = 0; i < task_list_view.items_size(); i++)
		task_items_.push_back(task_list_view.items(i));
}

void ListTask::load_task_menu()
{
	console_view_->activate_console([&]()
	{
		load_tasks();

		console_view_->reset_tasks();
		generate_tasks_list();
		add_back_task();

		ConsoleWriter::print_back_option();

		console_view_->run_command_input();

		if (console_view_->is_task_set())
		{
			show_task_info(console_view_->get_active_task_index());
			return true;
		}
		else if (console_view_->is_command_set(ConsoleCommandType::BACK_TO_PREVIOUS_MENU))
		{
			return false;
		}

		ConsoleWriter::print_undefined_action_message();
		return true;
	});
}

void ListTask::generate_tasks_list()
{
	std::cout << "My tasks list:" << std::endl;
	std::cout << "----------------" << std::endl;

	if (task_items_.empty())
	{
		std::cout << "<no tasks>\n";
	}

	for (int index = 0; index < task_items_.size(); ++index)
	{
		std::string taskIndex = std::to_string(index + 1);
		std::cout << "(" << std::to_string(index + 1) << ") " << task_items_[index].description().value() << "\n";

		console_view_->add_task_view_command(
			std::make_shared<TCLAP::SwitchArg>(taskIndex, "task_number" + taskIndex, "Choose task" + taskIndex, false)
		);
	}
}

void ListTask::show_task_info(int active_task_number)
{
	auto & taskItem = task_items_[active_task_number];

	ConsoleWriter::print_task_description(taskItem);

	console_view_->activate_console([&] ()
	{
		console_view_->reset_tasks();

		add_back_task();

		ConsoleWriter::print_back_option();

		console_view_->run_command_input();
		if (console_view_->is_command_set(ConsoleCommandType::BACK_TO_PREVIOUS_MENU))
		{
			return false;
		}

		ConsoleWriter::print_undefined_action_message();
		return true;
	});
}

void ListTask::add_back_task()
{
	console_view_->add_simple_command(
		ConsoleCommandType::BACK_TO_PREVIOUS_MENU,
		std::make_shared<TCLAP::SwitchArg>("b", "Back", "Go to previous menu", false)
	);
}

} // namespace todolist
} // namespace examples
} // namespace spine
