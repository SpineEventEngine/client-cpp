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

#include "create_task.h"
#include "create_task_label.h"
#include "command_handler/command_handler.h"

#include "console_view/console_view_impl.h"
#include "console_view/console_writer.h"
#include "Poco/UUIDGenerator.h"

#include <iostream>

namespace spine {
namespace examples {
namespace todolist {

CreateTask::CreateTask(
	std::shared_ptr<ConsoleView> console_view,
	std::shared_ptr<CommandHandler> command_handler
)
	: BaseTask(console_view, command_handler)
{
	wizard_id_ = TaskCreationId::default_instance().New();
	std::string task_id = generate_unique_id();
	wizard_id_->set_value(std::move(task_id));

	task_id_ = TaskId::default_instance().New();
	std::string unique_task_id = generate_unique_id();
	task_id_->set_value(unique_task_id);
	

	task_priority_ = TaskPriority::TP_UNDEFINED;
	task_details_is_already_set = false;
}

void CreateTask::run_task_creation()
{
	start_task_creation();
	console_view_->activate_console([&]()
	{
		std::cout << "Create task menu" << std::endl;
		std::cout << "----------------" << std::endl;
		console_view_->add_simple_command(ConsoleCommandType::ADD_DESCRIPTION, "d", "Description", "Add/Edit description");
		console_view_->add_simple_command(ConsoleCommandType::ADD_PRIORITY, "p", "Priority", "Add/Edit Priority");
		console_view_->add_simple_command(ConsoleCommandType::NEXT_STAGE, "n", "Next_stage", "Next stage");
		console_view_->add_simple_command(ConsoleCommandType::CANCEL_TASK, "c", "Cancel", "Cancel Task");
		console_view_->add_simple_command(ConsoleCommandType::BACK_TO_PREVIOUS_MENU, "b", "Back", "Go to previous menu");
		console_view_->run_command_input();
		switch (console_view_->get_active_task())
		{
			case ConsoleCommandType::ADD_DESCRIPTION:
				add_task_description();
				break;
			case ConsoleCommandType::ADD_PRIORITY:
				add_task_priority();
				break;
			case ConsoleCommandType::CANCEL_TASK:
				cancel_task();
				return false;
			case ConsoleCommandType::NEXT_STAGE:
				return move_to_next_stage();
				break;
			case ConsoleCommandType::BACK_TO_PREVIOUS_MENU:
				return false;
			default:
				return true;
		}
		return true;
	});
}

void CreateTask::start_task_creation()
{
	StartTaskCreation * start_task_creation = StartTaskCreation::default_instance().New();
	start_task_creation->set_allocated_id(wizard_id_);
	start_task_creation->set_allocated_task_id(task_id_);

	command_handler_->post_command(*start_task_creation);
}

void CreateTask::add_task_description()
{
	std::cout << "Please enter the task description:\n";
	std::string previous_description = task_description_;
	task_description_.clear();
	std::getline(std::cin, task_description_);
	update_description(previous_description);
	std::cout << "Task description updated.\n";
}

void CreateTask::update_description(const std::string & previous_description)
{
	if (!task_details_is_already_set)
		return;

	UpdateTaskDescription * update_task_description = UpdateTaskDescription::default_instance().New();
	change::StringChange * string_change = change::StringChange::default_instance().New();
	string_change->set_new_value(task_description_);
	string_change->set_previous_value(previous_description);
	update_task_description->set_allocated_description_change(string_change);
	update_task_description->set_allocated_id(task_id_);
	command_handler_->post_command(* update_task_description);
}

void CreateTask::add_task_priority()
{
	TaskPriority previous_task_priority = task_priority_;
	task_priority_ = generate_task_priority();
	update_priority(previous_task_priority);
	std::cout << "Task priority updated.\n";
}

void CreateTask::update_priority(TaskPriority previous_task_priority)
{
	if (!task_details_is_already_set)
		return;

	UpdateTaskPriority *  update_task_priority = UpdateTaskPriority::default_instance().New();
	PriorityChange * priority_change = PriorityChange::default_instance().New();
	priority_change->set_new_value(task_priority_);
	priority_change->set_previous_value(previous_task_priority);
	update_task_priority->set_allocated_priority_change(priority_change);
	update_task_priority->set_allocated_id(task_id_);
	command_handler_->post_command(* update_task_priority);
}

void CreateTask::cancel_task()
{
	CancelTaskCreation cancel_task_creation;
	cancel_task_creation.set_allocated_id(wizard_id_);
	command_handler_->post_command(cancel_task_creation);
}

bool CreateTask::move_to_next_stage()
{
	if (task_description_.empty())
	{
		std::cout << "Task description is not add.\n" << "Please add task description.\n";
		return true;
	}

	TaskDescription *task_description = TaskDescription::default_instance().New();
	task_description->set_value(task_description_);

	SetTaskDetails * task_details = SetTaskDetails::default_instance().New();
	task_details->set_allocated_id(wizard_id_);
	task_details->set_priority(task_priority_);
	task_details->set_allocated_description(task_description);

	command_handler_->post_command(*task_details);
	task_details_is_already_set = true;
	return assign_task_labels();
}

bool CreateTask::assign_task_labels()
{
	CreateTaskLabel create_task_label(console_view_, command_handler_, wizard_id_);
	return create_task_label.add_labels();
}

TaskPriority CreateTask::generate_task_priority()
{
	std::cout << "Please enter the task priority:\n";
	while (true)
	{
		std::cout
			<< "(1) - HIGH \n"
			<< "(2) - NORMAL \n"
			<< "(3) - LOW    \n";

		int task_priority;
		std::cin >> task_priority;
		std::cin.ignore();
		if (TaskPriority::HIGH <= task_priority <= TaskPriority::LOW) {
			return static_cast<TaskPriority>(task_priority);
		}
		else {
			std::cout << "The value is incorrect. Please choose the proper task priority.\n";
		}
	}
}

std::string CreateTask::generate_unique_id()
{
	Poco::UUIDGenerator generator;
	return generator.createRandom().toString();
}

} // namespace todolist
} // namespace examples
} // namespace spine
