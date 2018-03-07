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
#include "create_task_label.h"
#include "task_completer.h"
#include "console_view/console_writer.h"
#include "console_view/console_view_impl.h"
#include "command_handler/command_handler_impl.h"
#include "resources/resources.h"

namespace spine {
namespace examples {
namespace todolist {

constexpr int MIN_TASK_NUMBER = 1;

CreateTaskLabel::CreateTaskLabel(
	std::shared_ptr<ConsoleView> console_view,
	std::shared_ptr<CommandHandler> command_handler,
	TaskCreationId * wizard_id
)
	: BaseTask(console_view, command_handler)
	, wizard_id_(wizard_id)
{
}

bool CreateTaskLabel::add_labels()
{
	bool assignment_result = true;
	AddLabels * add_labels_command = AddLabels::default_instance().New();
	add_labels_command->set_allocated_id(wizard_id_);

	console_view_->activate_console([&]()
	{
		std::cout << resources::messages::TASK_LABEL_MENU << std::endl;
		std::cout << resources::command_line::LINE_SEPARATOR << std::endl;

		print_assigned_labels();
		initialize_commands();

		return process_command(add_labels_command, assignment_result);
	});

	return assignment_result;
}

void CreateTaskLabel::initialize_commands()
{
	console_view_->add_simple_command(
		ConsoleCommandType::ASSIGN_NEW_LABEL,
		resources::tasks_menu::NEW_LABEL_SHORTCUT,
		resources::tasks_menu::NEW_LABEL_COMMAND,
		resources::tasks_menu::NEW_LABEL_INFO
	);
	console_view_->add_simple_command(
		ConsoleCommandType::ASSIGN_EXISTING_LABEL,
		resources::tasks_menu::EXISTING_LABEL_SHORTCUT,
		resources::tasks_menu::EXISTING_LABEL_COMMAND,
		resources::tasks_menu::EXISTING_LABEL_INFO
	);
	console_view_->add_simple_command(
		ConsoleCommandType::REMOVE_LABEL,
		resources::tasks_menu::REMOVE_LABEL_SHORTCUT,
		resources::tasks_menu::REMOVE_LABEL_COMMAND,
		resources::tasks_menu::REMOVE_LABEL_INFO
	);
	console_view_->add_simple_command(
		ConsoleCommandType::NEXT_STAGE,
		resources::tasks_menu::NEXT_STAGE_SHORTCUT,
		resources::tasks_menu::NEXT_STAGE_COMMAND,
		resources::tasks_menu::NEXT_STAGE_INFO
	);
	console_view_->add_simple_command(
		ConsoleCommandType::CANCEL_TASK,
		resources::tasks_menu::CANCEL_SHORTCUT,
		resources::tasks_menu::CANCEL_COMMAND,
		resources::tasks_menu::CANCEL_INFO
	);

	console_view_->add_simple_command(
		ConsoleCommandType::BACK_TO_PREVIOUS_MENU,
		resources::tasks_menu::BACK_SHORTCUT,
		resources::tasks_menu::BACK_COMMAND,
		resources::tasks_menu::BACK_INFO
	);
}

bool CreateTaskLabel::process_command(AddLabels * add_labels_command, bool & assignment_result)
{
	console_view_->run_command_input();
	switch (console_view_->get_active_task())
	{
		case ConsoleCommandType::ASSIGN_NEW_LABEL:
			assign_new_label(add_labels_command);
			break;
		case ConsoleCommandType::ASSIGN_EXISTING_LABEL:
			assign_existing_labels(add_labels_command);
			break;
		case ConsoleCommandType::REMOVE_LABEL:
			remove_task_label(add_labels_command);
			break;
		case ConsoleCommandType::NEXT_STAGE:
			assignment_result = finish_label_assignment(add_labels_command);
			return assignment_result;
		case ConsoleCommandType::CANCEL_TASK:
			cancel_task();
			assignment_result = false;
			return false;
		case ConsoleCommandType::BACK_TO_PREVIOUS_MENU:
			assignment_result = true;
			return false;
		default:
			return true;
	}
	return true;
}

void CreateTaskLabel::cancel_task()
{
	CancelTaskCreation cancel_task_creation;
	cancel_task_creation.set_allocated_id(wizard_id_);
	command_handler_->post_command(cancel_task_creation);
}

void CreateTaskLabel::assign_new_label(AddLabels * add_labels_command)
{
	std::cout << resources::messages::PLEASE_ENTER_THE_TASK_LABEL << std::endl;
	std::string label_title;
	std::getline(std::cin, label_title);
	LabelDetails * label_details = add_labels_command->add_new_labels();
	label_details->set_title(label_title);

	LabelColor label_color = generate_label_color();
	label_details->set_color(label_color);

	new_labels_.push_back(label_details);
}


void CreateTaskLabel::assign_existing_labels(AddLabels * add_labels_command)
{
	auto task_labels = command_handler_->get_labels();
	std::cout << resources::messages::EXISTING_LABELS;
	if (task_labels.empty())
	{
		std::cout << resources::messages::NO_EXISTING_LABELS;
		return;
	}

	for (int i = 0; i < task_labels.size(); ++i)
	{
		TaskLabel * label = task_labels[i];
		ConsoleWriter::print_existing_task_label_info(
			std::to_string(i + MIN_TASK_NUMBER),
			label->title(),
			label_color_to_string(label->color())
		);
	}

	while (true)
	{
		std::cout << resources::messages::PLEASE_CHOOSE_THE_LABEL_NUMBER;
		int label_number = 0;
		std::cin >> label_number;
		std::cin.ignore();
		if (MIN_TASK_NUMBER < label_number < task_labels.size())
		{
			auto * existing_label = add_labels_command->add_existing_labels();
			existing_label->set_value(task_labels[label_number - MIN_TASK_NUMBER]->id().value());
		}
		else
		{
			std::cout << resources::messages::LABEL_NUMBER_IS_INCORRECT;
		}
	}
}

void CreateTaskLabel::remove_task_label(AddLabels * add_labels_command)
{
	if (no_assigned_labels())
	{
		std::cout << resources::messages::NO_LABELS_ON_THIS_TASK << std::endl;
		return;
	}
	
	print_assigned_labels();
	int task_labels_count = existing_labels_.size() + new_labels_.size();

	while (true)
	{
		std::cout << resources::messages::PLEASE_SELECT_NUMBER_YOU_WANT_TO_REMOVE;
		int label_number;
		std::cin >> label_number;
		std::cin.ignore();
		if (MIN_TASK_NUMBER < label_number < task_labels_count)
		{
			remove_label_from_list(add_labels_command, label_number);	
			return;
		}
		else
		{
			std::cout << resources::messages::LABEL_NUMBER_IS_INCORRECT << std::endl;
		}
	}
}

void CreateTaskLabel::remove_label_from_list(AddLabels * add_labels_command, int label_number)
{
	if (label_number <= new_labels_.size())
	{
		--label_number;
		new_labels_.erase(new_labels_.begin() + label_number);
		update_new_labels(add_labels_command);
	}
	else
	{
		label_number -= new_labels_.size();
		--label_number;
		existing_labels_.erase(existing_labels_.begin() + label_number);
		update_existing_labels(add_labels_command);
	}

	ConsoleWriter::print_label_removed_from_task_message(std::to_string(label_number));
}

void CreateTaskLabel::update_new_labels(AddLabels * add_labels_command)
{
	add_labels_command->clear_new_labels();
	std::for_each(new_labels_.begin(), new_labels_.end(), [&](LabelDetails * label_details)
	{
		LabelDetails * updated_label_details = add_labels_command->add_new_labels();
		updated_label_details->set_color(label_details->color());
		updated_label_details->set_title(label_details->title());
	});
}

void CreateTaskLabel::update_existing_labels(AddLabels * add_labels_command)
{
	add_labels_command->clear_existing_labels();
	std::for_each(existing_labels_.begin(), existing_labels_.end(), [&](TaskLabel * task_label)
	{
		LabelId * updated_task_label = add_labels_command->add_existing_labels();
		updated_task_label->set_value(task_label->id().value());
	});
}

bool CreateTaskLabel::finish_label_assignment(AddLabels * add_labels_command)
{
	command_handler_->post_command(*add_labels_command);
	TaskCompleter task_completer(console_view_, command_handler_, wizard_id_);
	return task_completer.run_complete_menu();
}

void CreateTaskLabel::print_assigned_labels()
{
	std::cout << resources::messages::ASSIGNED_LABELS;
	if (no_assigned_labels())
	{
		std::cout << resources::messages::NO_ASSIGNED_LABELS << std::endl;
		return;
	}
	
	for (int i = 0; i < new_labels_.size(); ++i)
	{
		auto * label_detail = new_labels_[i];

		ConsoleWriter::print_label_number(std::to_string(i + MIN_TASK_NUMBER));
		ConsoleWriter::print_label_info(
			label_detail->title(),
			label_color_to_string(label_detail->color())
		);
	}

	for (int i = 0; i < existing_labels_.size(); ++i)
	{
		auto * task_label = existing_labels_[i];
		ConsoleWriter::print_label_number(std::to_string(i + MIN_TASK_NUMBER));
		ConsoleWriter::print_label_info(
			task_label->title(),
			label_color_to_string(task_label->color())
		);
	}
}

bool CreateTaskLabel::no_assigned_labels()
{
	return new_labels_.empty() && existing_labels_.empty();
}

} // namespace todolist
} // namespace examples
} // namespace spine