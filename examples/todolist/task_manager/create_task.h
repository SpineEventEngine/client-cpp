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

#ifndef TODOLIST_CREATE_TASK_H
#define TODOLIST_CREATE_TASK_H

#include <memory>
#include <string>

#include "todolist/model.pb.h"
#include "todolist/c/commands.pb.h"

#include "base_task.h"

namespace spine {
namespace examples {
namespace todolist {

class ConsoleView;
class CommandHandler;

class CreateTask : public BaseTask
{
public:
	CreateTask(
		std::shared_ptr<ConsoleView> console_view, 
		std::shared_ptr<CommandHandler> command_handler);

public:
	void run_task_creation();

private:
	void start_task_creation();
	void add_task_description();
	void add_task_priority();
	void cancel_task();

	void update_description(const std::string & previous_description);
	void update_priority(TaskPriority task_priority);

	void initialize_commands();

    MenuResult process_command();
    MenuResult move_to_next_stage();
	MenuResult assign_task_labels();

private:
	TaskCreationId * wizard_id_;
	TaskId * task_id_;
	TaskPriority task_priority_;

	std::string task_description_;
	bool task_details_is_already_set;
};

} // namespace todolist
} // namespace examples
} // namespace spine

#endif // TODOLIST_CREATE_TASK_H
