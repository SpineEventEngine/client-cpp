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

#ifndef TODOLIST_CREATE_TASK_LABEL_H
#define TODOLIST_CREATE_TASK_LABEL_H

#include <memory>
#include <string>

#include "base_task.h"

#include "todolist/model.pb.h"
#include "todolist/c/commands.pb.h"

namespace spine {
namespace examples {
namespace todolist {

class ConsoleView;
class CommandHandler;

class CreateTaskLabel : BaseTask
{
public:
	CreateTaskLabel(
		std::shared_ptr<ConsoleView> console_view,
		std::shared_ptr<CommandHandler> command_handler,
		TaskCreationId * wizard_id);

	bool add_labels();

private:
	void assign_new_label(AddLabels * add_labels_command);
	void assign_existing_labels(AddLabels * add_labels_command);
	void remove_task_label(AddLabels * add_labels_command);
	void print_assigned_labels();
	void cancel_task();

	void update_new_labels(AddLabels * add_labels_command);
	void update_existing_labels(AddLabels * add_labels_command);

	bool finish_label_assignment(AddLabels * add_labels_command);
	bool no_assigned_labels();

	LabelColor assign_label_color();

private:
	std::vector<LabelDetails * > new_labels_;
	std::vector<TaskLabel * > existing_labels_;

	TaskCreationId * wizard_id_;
};

} // namespace todolist
} // namespace examples
} // namespace spine

#endif // TODOLIST_CREATE_TASK_LABEL_H
