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

namespace spine {
namespace examples {
namespace todolist {

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
		std::cout << "Task Labels menu" << std::endl;
		std::cout << "----------------" << std::endl;
		print_assigned_labels();
		console_view_->add_simple_command(ConsoleCommandType::ASSIGN_NEW_LABEL, "a", "Assign_new_label", "Assign new label");
		console_view_->add_simple_command(ConsoleCommandType::ASSIGN_EXISTING_LABEL, "e", "Assign_existing_label", "Assign existing label");
		console_view_->add_simple_command(ConsoleCommandType::REMOVE_LABEL, "r", "remove_label", "Remove label from task");
		console_view_->add_simple_command(ConsoleCommandType::NEXT_STAGE, "n", "Next_stage", "Next stage");
		console_view_->add_simple_command(ConsoleCommandType::CANCEL_TASK, "c", "Cancel", "Cancel Task");
		console_view_->add_simple_command(ConsoleCommandType::BACK_TO_PREVIOUS_MENU, "b", "Back", "Go to previous menu");
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
			assignment_result =  finish_label_assignment(add_labels_command);
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
	});

	return assignment_result;
}

void CreateTaskLabel::cancel_task()
{
	CancelTaskCreation cancel_task_creation;
	cancel_task_creation.set_allocated_id(wizard_id_);
	command_handler_->post_command(cancel_task_creation);
}

void CreateTaskLabel::assign_new_label(AddLabels * add_labels_command)
{
	std::cout << "Please enter the label title" << std::endl;
	std::string label_title;
	std::getline(std::cin, label_title);
	LabelDetails * label_details = add_labels_command->add_new_labels();
	label_details->set_title(label_title);

	LabelColor label_color = assign_label_color();
	label_details->set_color(label_color);

	new_labels_.push_back(label_details);
}

LabelColor CreateTaskLabel::assign_label_color()
{
	std::cout << "Please enter the label color:\n";
	while (true)
	{
		std::cout
			<< "(1) - RED \n"
			<< "(2) - GREEN \n"
			<< "(3) - BLUE    \n"
			<< "(4) - GRAY   \n";

		int label_color = 0;
		std::cin >> label_color;
		std::cin.ignore();
		if (LabelColor::RED <= label_color <= LabelColor::GRAY) {
			return static_cast<LabelColor>(label_color);
		}
		else {
			std::cout << "The value is incorrect. Please choose the label color.\n";
		}
	}
}

void CreateTaskLabel::assign_existing_labels(AddLabels * add_labels_command)
{
	auto task_labels = command_handler_->get_labels();
	std::cout << "Existing labels :\n";
	if (task_labels.empty())
	{
		std::cout << "<No existing labels.>\n";
		return;
	}

	for (int i = 0; i < task_labels.size(); ++i)
	{
		TaskLabel * label = task_labels[i];
		std::cout << "(" << std::to_string(i + 1) << ")" << " -  [Title:" << label->title() << " Color : " << label->color() << "]\n";
	}

	while (true)
	{
		std::cout << "Please choose a number of existing label:\n";
		int label_number = 0;
		std::cin >> label_number;
		std::cin.ignore();
		if (1 < label_number < task_labels.size())
		{
			add_labels_command->add_existing_labels()->set_value(task_labels[label_number - 1]->id().value());
		}
		else {
			std::cout << "The value is incorrect. Please choose the label number.\n";
		}
	}
}

void CreateTaskLabel::remove_task_label(AddLabels * add_labels_command)
{
	if (no_assigned_labels())
	{
		std::cout << "You did not assign any label to this task.\n" << std::endl;
		return;
	}
	
	print_assigned_labels();
	int task_labels_count = existing_labels_.size() + new_labels_.size();

	while (true)
	{
		std::cout << "Please select label number you want to remove.\n";
		int label_number;
		std::cin >> label_number;
		std::cin.ignore();
		if (1 < label_number < task_labels_count)
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
			std::cout << "Label # " << std::to_string(label_number) << " removed from task.\n";
			return;
		}
		else {
			std::cout << "Label number is incorrect. Please choose the correct number.\n" << std::endl;
		}
	}
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
	std::cout << "Assigned labels:\n";
	if (no_assigned_labels())
	{
		std::cout << "<No assigned labels>" << std::endl;
	}
	
	unsigned int label_counter = 0;

	std::for_each(new_labels_.begin(), new_labels_.end(), [&](LabelDetails * label_detail)
	{
		std::cout << "Label #" << " " << std::to_string(label_counter + 1) << ":" << std::endl;
		std::cout << "[Title : " << label_detail->title() << ", Color :" << label_detail->color() << "]" << std::endl;
		++label_counter;
	});
	std::for_each(existing_labels_.begin(), existing_labels_.end(), [&](TaskLabel * task_label)
	{
		std::cout << "Label #" << " " << std::to_string(label_counter + 1) << ":" << std::endl;
		std::cout << "[Title : " << task_label->title() << ", Color :" << task_label->color() <<  "]" << std::endl;
		++label_counter;
	});
}

bool CreateTaskLabel::no_assigned_labels()
{
	return new_labels_.empty() && existing_labels_.empty();
}

} // namespace todolist
} // namespace examples
} // namespace spine